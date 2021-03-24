#pragma once
#include "application.hpp"
#include "ECS/Components.h"

Manager manager;
SDL_Renderer *Application::renderer = nullptr;
SDL_Event Application::event;
std::vector<ColliderComponent *> Application::colliders;
auto &Player(manager.addEntity());
Application ::Application()
{
}
Application ::~Application()
{
}
void Application ::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    isRunning = true;
    Player.addComponent<TransformComponent>(0, 0, 32, 32, 1);
    Player.addComponent<SpriteComponent>("player.png");
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
}
void Application ::handleEvents()
{
    SDL_PollEvent(&Application::event);
    switch (Application::event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        
    default:
        break;
    }
}
void Application ::update()
{
    manager.refresh();
    manager.update();
    for (auto cc : colliders)
    {
        if (Collision::AABB(Player.getComponent<ColliderComponent>(), *cc) && cc->tag == "wall")
        {
            Player.getComponent<TransformComponent>().velocity * -1;
        }
    }
}
void Application ::render()
{
    SDL_RenderClear(renderer);
    manager.draw();
    SDL_RenderPresent(renderer);
}
void Application ::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
void Application:: AddTile(TileComponent::TileType id, int x, int y){
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x,y,32,32,id);
}