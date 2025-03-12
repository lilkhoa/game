#include "Food.h"

// Constructor
Food::Food(int init_x, int init_y) {
    x = init_x;
    y = init_y;

    food_texture = LoadTexture("assets/apple.png");
}

// Destructor
Food::~Food() {
    UnloadTexture(food_texture);
}

// Draw method
void Food::draw() {
    DrawTexture(food_texture, x, y, RED);
}

// Get position method
pair<int, int> Food::get_position() {
    return {x, y};
}

// Set position method
void Food::set_position(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}