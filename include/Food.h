#ifndef FOOD_H
#define FOOD_H

#include "env.h"

using namespace std;

class Food {
public:
    Food(int init_x, int init_y);
    ~Food();

    void draw();
    pair<int, int> get_position();
    void set_position(int new_x, int new_y);

private:
    int x, y;
    Texture2D food_texture;
};

#endif // FOOD_H