#include "Game.h"

// Constructor
Game::Game() {
    snake = new Snake();
    food = new Food(BORDER_WIDTH + rand() % (WIDTH - 2 * BORDER_WIDTH - FOOD_SIZE - 50), 
                        BORDER_WIDTH + rand() % (HEIGHT - 2 * BORDER_WIDTH - FOOD_SIZE - 50));
    score = 0;
    background = LoadTexture("assets/bg.jpg");
    gameFont = LoadFontEx("assets/font.ttf", 32, 0, 250);
    currentState = START_SCREEN;

    // Create a render texture for the border
    RenderTexture2D borderRender = LoadRenderTexture(WIDTH, HEIGHT);
    BeginTextureMode(borderRender);
    ClearBackground(BLANK);
    
    // Draw border on the texture
    DrawRectangleLinesEx(
        (Rectangle){ 
            10, 
            10, 
            1260, 
            700 
        }, 
        BORDER_WIDTH, 
        BORDER_COLOR
    );
    
    EndTextureMode();
    borderTexture = borderRender.texture;
}

// Destructor
Game::~Game() {
    delete snake;
    delete food;
    UnloadTexture(background);
    UnloadTexture(borderTexture);
}

// Play method
void Game::play() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        int game_over = 0;
        switch (currentState) {
            case START_SCREEN:
                draw_start_screen();
                handle_start_screen_input();
                break;

            case PLAYING:
                game_over = snake->move();
                if (game_over == 0) {
                    currentState = GAME_OVER;
                }
                ClearBackground(RAYWHITE);
                DrawTexture(background, 0, 0, WHITE);
                DrawTexture(borderTexture, 0, 0, WHITE);
                snake->draw();
                food->draw();
                display_score();
                snake_eat_food();
                break;

            case GAME_OVER:
                // First draw the game scene (same as in PLAYING state)
                ClearBackground(RAYWHITE);
                DrawTexture(background, 0, 0, WHITE);
                DrawTexture(borderTexture, 0, 0, WHITE);
                snake->draw();
                food->draw();
                display_score();
                
                // Then overlay the game over screen
                draw_game_over();
                handle_game_over_input();
                break;
        }
        WaitTime(0.1);
        EndDrawing();
    }
}

// Private methods
// Snake eat food
void Game::snake_eat_food() {
    pair<int, int> food_pos = food->get_position();
    pair<int, int> snake_pos = snake->get_position();
    
    // Create rectangle structures for snake head and food
    Rectangle snakeHead = { 
        (float)snake_pos.first, 
        (float)snake_pos.second, 
        (float)SNAKE_SIZE, 
        (float)SNAKE_SIZE 
    };
    
    Rectangle foodRect = { 
        (float)food_pos.first, 
        (float)food_pos.second, 
        (float)FOOD_SIZE, 
        (float)FOOD_SIZE 
    };

    if (CheckCollisionRecs(snakeHead, foodRect)) {
        snake->grow();
        food->set_position(
            BORDER_WIDTH + rand() % (WIDTH - 2 * BORDER_WIDTH - FOOD_SIZE - 50), 
            BORDER_WIDTH + rand() % (HEIGHT - 2 * BORDER_WIDTH - FOOD_SIZE - 50)
        );
        score += 10;
    }
}

// Draw start screen method
void Game::draw_start_screen() {
    ClearBackground(RAYWHITE);
    
    // Draw background with scaling
    Rectangle sourceRec = { 0, 0, (float)background.width, (float)background.height };
    Rectangle destRec = { 0, 0, (float)WIDTH, (float)HEIGHT };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(background, sourceRec, destRec, origin, 0.0f, WHITE);
    
    // Draw border
    DrawTexture(borderTexture, 0, 0, WHITE);
    
    // Draw title
    DrawTextEx(gameFont, "SNAKE GAME", (Vector2){ WIDTH/2 - 170, 100 }, 60, 2, DARKGREEN);
    
    // Draw menu options
    DrawTextEx(gameFont, "PRESS ENTER TO START", (Vector2){ WIDTH/2 - 180, HEIGHT/2 }, 32, 2, BLACK);
    
    // Draw instructions
    DrawTextEx(gameFont, "Use arrow keys to control the snake", (Vector2){ WIDTH/2 - 230, HEIGHT/2 + 130 }, 24, 2, DARKGRAY);
}

// Start screen input method
void Game::handle_start_screen_input() {
    if (IsKeyPressed(KEY_ENTER)) {
        currentState = PLAYING;
    }
}

// Game over screen method
void Game::draw_game_over() {
    DrawRectangle(0, 0, WIDTH, HEIGHT, ColorAlpha(BLACK, 0.5f));    
    DrawTextEx(gameFont, "GAME OVER", (Vector2){ WIDTH/2 - 110, HEIGHT/2 - 40 }, 40, 2, RED);
    DrawTextEx(gameFont, TextFormat("SCORE: %i", score), (Vector2){ WIDTH/2 - 80, HEIGHT/2 + 10 }, 32, 2, WHITE);
    DrawTextEx(gameFont, "PRESS R TO RESTART", (Vector2){ WIDTH/2 - 130, HEIGHT/2 + 60 }, 24, 2, WHITE);
}

// Game over input method
void Game::handle_game_over_input() {
    if (IsKeyPressed(KEY_R)) {
        delete snake;
        delete food;
        snake = new Snake();
        food = new Food(
            BORDER_WIDTH + rand() % (WIDTH - 2 * BORDER_WIDTH - FOOD_SIZE - 50), 
            BORDER_WIDTH + rand() % (HEIGHT - 2 * BORDER_WIDTH - FOOD_SIZE - 50)
        );
        score = 0;
        currentState = PLAYING;
    }
}

// Display score method
void Game::display_score() {
    DrawText(TextFormat("Score: %i", score), 10, 10, 20, BLACK);
}