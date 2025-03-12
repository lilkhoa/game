#ifndef GAME_H
#define GAME_H

#include "init.h"
#include "Snake.h"
#include "Food.h"

class Game {
public:
    Game();
    ~Game();

    void play();

private:
    void snake_eat_food();
    void handle_start_screen_input();
    void draw_start_screen();
    void handle_game_over_input();
    void draw_game_over();
    void display_score();

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

#endif // GAME_H