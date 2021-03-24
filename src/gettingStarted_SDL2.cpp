#include "SDL2/SDL.h"
#include <iostream>
using namespace std;
int main(int argv, char** args)
{
     SDL_Init(SDL_INIT_EVERYTHING);

                SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

                SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

                //Struct for handling events
                SDL_Event input;

                //Boolean to find out whether the game is stopped or not
                //Of course, it will be false at start
                bool quit = false;

                //For selecting renderer's draw color
                int r = 0, g = 255, b = 0;

                while (!quit) //Same as while(quit == false)
                {

                                //---Event polling method---
                                //It runs until the number of events to be polled gets to zero
                                while (SDL_PollEvent(&input) > 0)
                                {

                                                //If the user did something which should
                                                //result in quitting of the game then...
                                                if (input.type == SDL_QUIT)
                                                {
                                                                //...go out of the while loop
                                                                quit = true;
                                                }
                                                //If the user pressed any key then...
                                                else if (input.type == SDL_KEYDOWN)
                                                {

                                                                //...randomize the renderer's draw color
                                                                r = rand() % 255;
                                                                g = rand() % 255;
                                                                b = rand() % 255;
                                                }

                                }
                                
                                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
                                SDL_RenderClear(renderer);
                                SDL_RenderPresent(renderer);
                }

                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
}