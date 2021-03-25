#pragma once
#ifndef _GAME_CPP_
#define _GAME_CPP_
#include "game.hpp"
#include "ECS/Components.h"
#include "ECS/NewComponent.h"
Manager manager;
SDL_Renderer *Game :: renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent *> Game::colliders;
auto &Player(manager.addEntity());
auto &tile0(manager.addEntity());
Game ::Game()
{
}
Game ::~Game()
{
}
void Game ::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
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
    // tile0.addComponent<TileComponent>(100, 100, 32, 32, TileComponent::TileType::water);
    // tile0.addComponent<SpriteComponent>(TileComponent::path);
    tile0.addComponent<NewComponent>(100,100,32,32,NewComponent::TileType:: water);
}
void Game ::handleEvents()
{
    SDL_PollEvent(&Game::event);
    switch (Game::event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:

    default:
        break;
    }
}
void Game ::update()
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
void Game ::render()
{
    SDL_RenderClear(renderer);
    manager.draw();
    SDL_RenderPresent(renderer);
}
void Game ::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
void Game::AddTile(TileComponent::TileType id, int x, int y)
{
    auto &tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id);
}
#endif