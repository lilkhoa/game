#include "Game.h"

int main() {
    InitWindow(WIDTH, HEIGHT, "Snake Game");
    SetTargetFPS(FPS);

    Game *game = new Game();
    game->play();
    delete game;

    CloseWindow();
    return 0;
}