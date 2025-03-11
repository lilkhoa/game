#include <iostream>
#include <vector>
#include <raylib.h>

#define WIDTH 1280
#define HEIGHT 720
#define FPS 30

#define SNAKE_SIZE 40
#define SNAKE_SPEED 40

#define FOOD_SIZE 40

#define BORDER_WIDTH 20
#define BORDER_COLOR DARKGREEN

using namespace std;

class Snake {
public:
    Snake(pair<int, int> init_pos = {440, 225}, int init_length = 2) {
        x = init_pos.first;
        y = init_pos.second;
        length = init_length;
        for (int i = 0; i < length; ++i) {
            body.push_back({x - i * SNAKE_SIZE, y});
        }
        direction = RIGHT;

        head_up = LoadTexture("assets/head_up.png");
        head_down = LoadTexture("assets/head_down.png");
        head_left = LoadTexture("assets/head_left.png");
        head_right = LoadTexture("assets/head_right.png");

        body_vertical = LoadTexture("assets/body_vertical.png");
        body_horizontal = LoadTexture("assets/body_horizontal.png");
        body_bottom_left = LoadTexture("assets/body_bottom_left.png");
        body_bottom_right = LoadTexture("assets/body_bottom_right.png");
        body_top_left = LoadTexture("assets/body_top_left.png");
        body_top_right = LoadTexture("assets/body_top_right.png");

        tail_up = LoadTexture("assets/tail_up.png");
        tail_down = LoadTexture("assets/tail_down.png");
        tail_left = LoadTexture("assets/tail_left.png");
        tail_right = LoadTexture("assets/tail_right.png");
    }

    ~Snake() {
        UnloadTexture(head_up);
        UnloadTexture(head_down);
        UnloadTexture(head_left);
        UnloadTexture(head_right);

        UnloadTexture(body_vertical);
        UnloadTexture(body_horizontal);
        UnloadTexture(body_bottom_left);
        UnloadTexture(body_bottom_right);
        UnloadTexture(body_top_left);
        UnloadTexture(body_top_right);

        UnloadTexture(tail_up);
        UnloadTexture(tail_down);
        UnloadTexture(tail_left);
        UnloadTexture(tail_right);
    }

    int move() {
        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }

        if (IsKeyPressed(KEY_UP) && direction != DOWN) {
            direction = UP;
        } else if (IsKeyPressed(KEY_DOWN) && direction != UP) {
            direction = DOWN;
        } else if (IsKeyPressed(KEY_LEFT) && direction != RIGHT) {
            direction = LEFT;
        } else if (IsKeyPressed(KEY_RIGHT) && direction != LEFT) {
            direction = RIGHT;
        }

        switch (direction) {
            case UP: y -= SNAKE_SPEED; break;
            case DOWN: y += SNAKE_SPEED; break;
            case LEFT: x -= SNAKE_SPEED; break;
            case RIGHT: x += SNAKE_SPEED; break;
        }
        body[0] = {x, y};

        return check_collision(); 
    }

    void draw() {
        for (int i = 0; i < length; ++i) {
            pair<int, int> segment = body[i];
            int segx = segment.first;
            int segy = segment.second;

            if (i == 0) {
                switch (direction) {
                    case UP:    DrawTexture(head_up, segx, segy, BLUE); break;
                    case DOWN:  DrawTexture(head_down, segx, segy, BLUE); break;
                    case LEFT:  DrawTexture(head_left, segx, segy, BLUE); break;
                    case RIGHT: DrawTexture(head_right, segx, segy, BLUE); break;
                }
            } else if (i == length - 1) {
                pair<int, int> prev_segment = body[i - 1];
                int prev_segx = prev_segment.first;
                int prev_segy = prev_segment.second;

                if (prev_segy < segy) {
                    DrawTexture(tail_down, segx, segy, BLUE);
                } else if (segy < prev_segy) {
                    DrawTexture(tail_up, segx, segy, BLUE);   
                } else if (segx < prev_segx) {
                    DrawTexture(tail_left, segx, segy, BLUE); 
                } else if (prev_segx < segx) {
                    DrawTexture(tail_right, segx, segy, BLUE); 
                }
            } else {
                pair<int, int> prev_segment = body[i - 1];
                int prev_segx = prev_segment.first, prev_segy = prev_segment.second;
                pair<int, int> next_segment = body[i + 1];
                int next_segx = next_segment.first, next_segy = next_segment.second;

                if ((prev_segx < segx && next_segx > segx) || (next_segx < segx && prev_segx > segx)) {
                    // Horizontal body segment
                    DrawTexture(body_horizontal, segx, segy, BLUE);
                } else if ((prev_segy < segy && next_segy > segy) || (next_segy < segy && prev_segy > segy)) {
                    // Vertical body segment
                    DrawTexture(body_vertical, segx, segy, BLUE);
                } else if ((prev_segx < segx && next_segy > segy) || (next_segx < segx && prev_segy > segy)) {
                    // Bottom-left corner (coming from left, going down or vice versa)
                    DrawTexture(body_bottom_left, segx, segy, BLUE);
                } else if ((prev_segx > segx && next_segy > segy) || (next_segx > segx && prev_segy > segy)) {
                    // Bottom-right corner (coming from right, going down or vice versa)
                    DrawTexture(body_bottom_right, segx, segy, BLUE);
                } else if ((prev_segy < segy && next_segx < segx) || (next_segy < segy && prev_segx < segx)) {
                    // Top-left corner (coming from above, going left or vice versa)
                    DrawTexture(body_top_left, segx, segy, BLUE);
                } else if ((prev_segy < segy && next_segx > segx) || (next_segy < segy && prev_segx > segx)) {
                    // Top-right corner (coming from above, going right or vice versa)
                    DrawTexture(body_top_right, segx, segy, BLUE);
                }
            }
        }
    }

    void grow() {
        body.push_back({body[length - 1].first, body[length - 1].second});
        length++;
    }

    pair<int, int> get_position() {
        return {x, y};
    }
    
private:
    int check_collision() {
        // Check border collision
        if (x <= 30 || x + SNAKE_SIZE >= WIDTH - 30 || 
            y <= 30 || y + SNAKE_SIZE >= HEIGHT - 30) {
            return 0;
        }
        
        // Check self collision
        for (int i = 1; i < length; i++) {
            if (x == body[i].first && y == body[i].second) {
                return 0;
            }
        }
        
        return 1;
    }

private:
    int x, y;
    vector<pair<int, int>> body;
    int length;
    enum Direction {UP=0, DOWN, LEFT, RIGHT} direction;

    // Image for snake
    Texture2D head_up, head_down, head_left, head_right;
    Texture2D body_vertical, body_horizontal, body_bottom_left, body_bottom_right, body_top_left, body_top_right;
    Texture2D tail_up, tail_down, tail_left, tail_right;
};

class Food {
public:
    Food(int init_x, int init_y) {
        x = init_x;
        y = init_y;

        food_texture = LoadTexture("assets/apple.png");
    }

    ~Food() {
        UnloadTexture(food_texture);
    }

    void draw() {
        DrawTexture(food_texture, x, y, RED);
    }

    pair<int, int> get_position() {
        return {x, y};
    }

    void set_position(int new_x, int new_y) {
        x = new_x;
        y = new_y;
    }
private:
    int x, y;
    Texture2D food_texture;
};

class Game {
public:
    Game() {
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

    ~Game() {
        delete snake;
        delete food;
        UnloadTexture(background);
        UnloadTexture(borderTexture);
        UnloadFont(gameFont);
    }

    void play() {
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

private:
    void snake_eat_food() {
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

    void draw_start_screen() {
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

    void handle_start_screen_input() {
        if (IsKeyPressed(KEY_ENTER)) {
            // Reset game state for a new game
            delete snake;
            snake = new Snake();
            
            food->set_position(BORDER_WIDTH + rand() % (WIDTH - 2 * BORDER_WIDTH - FOOD_SIZE - 50),
                              BORDER_WIDTH + rand() % (HEIGHT - 2 * BORDER_WIDTH - FOOD_SIZE - 50));
            score = 0;
            
            // Change state to PLAYING
            currentState = PLAYING;
        }
    }

    void handle_game_over_input() {
        if (IsKeyPressed(KEY_R)) {
            // Restart the game
            delete snake;
            snake = new Snake();
            
            food->set_position(BORDER_WIDTH + rand() % (WIDTH - 2 * BORDER_WIDTH - FOOD_SIZE - 50),
                              BORDER_WIDTH + rand() % (HEIGHT - 2 * BORDER_WIDTH - FOOD_SIZE - 50));
            score = 0;
            
            currentState = PLAYING;
        }
    }

    void draw_game_over() {
        // Semi-transparent overlay
        DrawRectangle(0, 0, WIDTH, HEIGHT, ColorAlpha(BLACK, 0.5f));
        
        // Game over text
        DrawTextEx(gameFont, "GAME OVER", (Vector2){ WIDTH/2 - 110, HEIGHT/2 - 40 }, 40, 2, RED);
        DrawTextEx(gameFont, TextFormat("SCORE: %i", score), (Vector2){ WIDTH/2 - 80, HEIGHT/2 + 10 }, 32, 2, WHITE);
        DrawTextEx(gameFont, "PRESS R TO RESTART", (Vector2){ WIDTH/2 - 130, HEIGHT/2 + 60 }, 24, 2, WHITE);
    }

    void display_score() {
        DrawText(TextFormat("Score: %i", score), 10, 10, 20, BLACK);
    }
private:
    Snake *snake;
    Food *food;
    int score;
    Texture2D background;
    Texture2D borderTexture;
    enum GameState {START_SCREEN=0, PLAYING, GAME_OVER} currentState;
    Texture2D titleTexture;
    Font gameFont;
};

int main() {
    InitWindow(WIDTH, HEIGHT, "Snake Game");
    SetTargetFPS(FPS);

    Game *game = new Game();
    game->play();
    delete game;

    CloseWindow();
    return 0;
}