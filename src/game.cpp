//tung yeu ngoc linh rat la nhieu luon <3
#pragma once
#ifndef _GAME_CPP_
#define _GAME_CPP_
#include "game.hpp"
#include "ECS/Components.h"
#include "ECS/NewComponent.h"
#include "map.cpp"

SDL_Renderer *Game ::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, 800, 640};
std::vector<ColliderComponent *> Game::colliders;
auto &Player(manager.addEntity());
auto &tile0(manager.addEntity());
auto &tiles(manager.getGroup(groupMap));
auto &players(manager.getGroup(groupPlayers));
auto &enemies(manager.getGroup(groupEnemies));
bool Game::isRunning = false;
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
    Map *map = new Map();
    map->loadMap("map.map", 25, 20);
    Player.addComponent<TransformComponent>(0, 0, 32, 32, 1);
    Player.addComponent<SpriteComponent>("player_anims.png", true);
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player_idle");
    Player.addGroup(groupPlayers);
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
    camera.x = Player.getComponent<TransformComponent>().position.x - 400;
    camera.y = Player.getComponent<TransformComponent>().position.y - 320;
    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > camera.w)
        camera.x = camera.w;
    if (camera.y > camera.h)
        camera.y = camera.h;
}
void Game ::render()
{
    SDL_RenderClear(renderer);
    for (auto &t : tiles)
    {
        t->draw();
    }
    for (auto &p : players)
    {
        p->draw();
    }
    for (auto &e : enemies)
    {
        e->draw();
    }
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
    // tile.addComponent<NewComponent>(100,100,32,32,NewComponent::TileType:: id);
}
#endif