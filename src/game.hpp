
#pragma once 
#ifndef _GAME_HPP_
#define  _GAME_HPP_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>
#include <iostream>
class AssetManager;
class ColliderComponent;
class Game
{
public:
    static SDL_Event event;
    static SDL_Renderer *renderer;
    Game();
    ~Game();
    void init(const char* title, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    static bool isRunning;
    static SDL_Rect camera;
    static AssetManager* assets;
    enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};
    bool running()
    {
        return isRunning;
    }
private:
    int cnt =0;
    SDL_Window *window;

};
#endif