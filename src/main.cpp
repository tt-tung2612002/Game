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
    game->init("hello", 1920,1080,true);
    while (game->running())
    {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
    game->clean();
    return 0;
}