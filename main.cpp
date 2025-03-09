#include <iostream>
#include <vector>
#include <raylib.h>

#define WIDTH 800
#define HEIGHT 450
#define FPS 10

#define SNAKE_SIZE 10
#define SNAKE_SPEED SNAKE_SIZE

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
        for (int i = 0; i < length; i++) {
            DrawRectangle(body[i].first, body[i].second, SNAKE_SIZE, SNAKE_SIZE, BLACK);
        }
    }

private:
    int check_collision() {

        if (x <= 0 || x + SNAKE_SIZE >= WIDTH || y <= 0 || y + SNAKE_SIZE >= HEIGHT) {
            CloseWindow();
            return 0;
        }

        // Check if the snake collides with itself
        switch (direction)
        {
        case UP:
            for (int i = 1; i < length; i++) {
                if (body[i].first == x && body[i].second + SNAKE_SIZE == y) {
                    CloseWindow();
                    return 0;
                }
            }
            break;

        case DOWN:
            for (int i = 1; i < length; i++) {
                if (body[i].first == x && body[i].second - SNAKE_SIZE == y) {
                    CloseWindow();
                    return 0;
                }
            }
            break;

        case LEFT:
            for (int i = 1; i < length; i++) {
                if (body[i].first + SNAKE_SIZE == x && body[i].second == y) {
                    CloseWindow();
                    return 0;
                }
            }
            break;

        case RIGHT:
            for (int i = 1; i < length; i++) {
                if (body[i].first - SNAKE_SIZE == x && body[i].second == y) {
                    CloseWindow();
                    return 0;
                }
            }
            break;
        
            return 0;
        }
        return 1;
    }

private:
    // Snake's position
    int x, y;
    vector<pair<int, int>> body;

    // Length of the snake
    int length;

    // Direction of the snake
    enum Direction {UP=0, DOWN, LEFT, RIGHT} direction;

};

class Food {};

int main () {
    InitWindow(WIDTH, HEIGHT, "Snake Game");
    SetTargetFPS(FPS);

    Snake snake({400, 225}, 12);
    // Food food(100, 100);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        snake.move();
        snake.draw();
        EndDrawing();
        WaitTime(0.01);
    }

    CloseWindow();
    return 0;
    
}