
#pragma once 
#ifndef _GAME_HPP_
#define  _GAME_HPP_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>
#include "ECS/TileComponent.hpp"
#include "ECS/ColliderComponent.hpp"
class Game
{
public:
    static SDL_Event event;
    static SDL_Renderer *renderer;
    static std:: vector<ColliderComponent*> colliders;
    Game();
    ~Game();
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    static void AddTile(TileComponent::TileType id,int x,int y);
    bool running()
    {
        return isRunning;
    }
private:
    bool isRunning;
    SDL_Window *window;
    
};
#endif