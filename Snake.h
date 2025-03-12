#ifndef SNAKE_H
#define SNAKE_H

#include "init.h"

using namespace std;

class Snake {
public:
    Snake(pair<int, int> init_pos = {75, 75}, int init_length = 2);
    ~Snake();

    int move();
    void draw();
    void grow();
    pair<int, int> get_position();

private:
    int check_collision();

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

#endif // SNAKE_H