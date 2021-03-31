#pragma once
#ifndef _GAME_CPP_
#define _GAME_CPP_
#include "game.hpp"
#include "TextureManager.cpp"
#include "map.cpp"
#include "ECS/Components.h"
#include "Vector2D.hpp"
#include "ECS/Collision.cpp"
#include "AssetManager.cpp"
#include "ECS/ECS.cpp"
Manager manager;
SDL_Renderer *Game ::renderer = nullptr;    
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, 800, 640};
AssetManager* Game::assets  = new AssetManager(&manager);
auto &Player(manager.addEntity());
auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));
auto &projectiles(manager.getGroup(Game::groupProjectiles));
bool Game::isRunning = false;
Game ::Game()
{
}
Game ::~Game()
{
}
void Game ::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        isRunning = true;
    }
    assets->AddTexture("terrain","background.png");
    assets->AddTexture("player","player_anims.png");
    Map *map = new Map("terrain",5,32);
    map->loadMap("map.map", 25, 10);
    Player.addComponent<TransformComponent>(4);
    Player.addComponent<SpriteComponent>("player", true);
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(groupPlayers);
    assets->CreateProjectile(Vector2D(600,600),200,2,"projectile");
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
    SDL_Rect playerCol = Player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = Player.getComponent<TransformComponent>().position;
    manager.refresh();
    manager.update();
    camera.x = Player.getComponent<TransformComponent>().position.x - 400;
    camera.y = Player.getComponent<TransformComponent>().position.y - 320;
    for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			Player.getComponent<TransformComponent>().position = playerPos;
		}
	}
    for (auto &p: projectiles){
        if (Collision::AABB(Player.getComponent<ColliderComponent>().collider,p->getComponent<ColliderComponent>().collider)){
            p->destroy();
        }
    }
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
    for (auto &c : colliders)
    {
        c->draw();
    }
    for (auto &p : players)
    {
        p->draw();
    }
    for (auto &p: projectiles){
        p->draw();
    }
    SDL_RenderPresent(renderer);
}
void Game ::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
#endif