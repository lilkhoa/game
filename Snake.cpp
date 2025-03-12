#include "Snake.h"

// Constructor
Snake::Snake(pair<int, int> init_pos, int init_length) {
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

// Destructor
Snake::~Snake() {
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

// Move method
int Snake::move() {
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

    return this->check_collision(); 
}

// Draw method
void Snake::draw() {
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

// Grow method
void Snake::grow() {
    body.push_back(body[length - 1]);
    length++;
}

// Get position method
pair<int, int> Snake::get_position() {
    return {x, y};
}

// Private method
// Check collision method
int Snake::check_collision() {
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