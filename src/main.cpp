#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "game.cpp"
int main(int argc, char *argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    Game *game = new Game();
    game->init("hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,900,600, false);
    while (game->running())
    {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }
    game->clean();
    return 0;
}