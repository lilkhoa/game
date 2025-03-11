#include <iostream>
#include <vector>
#include <raylib.h>

#define WIDTH 800
#define HEIGHT 450
#define FPS 30

#define SNAKE_SIZE 10
#define SNAKE_SPEED 10

#define FOOD_SIZE 10

using namespace std;

class Snake {
public:
    Snake(pair<int, int> init_pos, int init_length = 2) {
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

        if (x <= 0) {
            x = WIDTH - SNAKE_SIZE;
        } else if (x >= WIDTH) {
            x = 0;
        } else if (y <= 0) {
            y = HEIGHT - SNAKE_SIZE;
        } else if (y >= HEIGHT) {
            y = 0;
        }

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
        snake = new Snake({400, 225}, 2);
        food = new Food(rand() % (WIDTH - FOOD_SIZE - 20) + 10, rand() % (HEIGHT - FOOD_SIZE - 20) + 10);
        score = 0;
    }

    ~Game() {
        delete snake;
        delete food;
    }

    void play() {
        bool game_over = false;

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            if (!game_over) game_over = !snake->move();
            snake->draw();
            food->draw();
            display_score();
            snake_eat_food();
            if (game_over) {
                display_game_over();
            }
            EndDrawing();
            WaitTime(0.01);
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
            food->set_position(rand() % (WIDTH - FOOD_SIZE - 20) + 10, rand() % (HEIGHT - FOOD_SIZE - 20) + 10);
            score += 10;
        }
    }

    void display_score() {
        DrawText(TextFormat("Score: %i", score), 10, 10, 20, BLACK);
    }

    void display_game_over() {
        DrawText("Game Over!", WIDTH / 2 - 50, HEIGHT / 2 - 10, 20, RED);
        DrawText(TextFormat("Your score: %i", score), WIDTH / 2 - 50, HEIGHT / 2 + 10, 20, RED);
    }

private:
    Snake *snake;
    Food *food;
    int score;
};

int main () {
    InitWindow(WIDTH, HEIGHT, "Snake Game");
    SetTargetFPS(FPS);

    Game *game = new Game();
    game->play();
    delete game;

    CloseWindow();
    return 0;
}