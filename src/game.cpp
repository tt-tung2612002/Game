#ifndef _GAME_CPP_
#define _GAME_CPP_
#include "game.hpp"
#include "TextureManager.cpp"
#include "map.cpp"
#include "ECS/Components.h"
#include "Vector2D.cpp"
#include "ECS/Collision.cpp"
#include "AssetManager.cpp"
#include "ECS/ECS.cpp"
#include <sstream>
bool onGround = false;
Manager manager;
SDL_Renderer *Game ::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, 800, 600};
AssetManager *Game::assets = new AssetManager(&manager);
auto &label(manager.addEntity());
auto &Player(manager.addEntity());
bool Game::isRunning = false;
void Game::Game::init(const char *title, int width, int height, bool fullscreen)
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
    if (TTF_Init() == -1)
    {
        std::cout << "Error : SDL_TTF" << std::endl;
    }
    assets->AddTexture("terrain", "background.png");
    assets->AddTexture("player", "player_anims.png");
    assets->AddTexture("projectile", "projectile.png");
    assets->AddFont("arial", "arial.ttf", 16);
    Map *map = new Map("terrain", 5, 32);
    map->loadMap("map.map", 25, 10);
    Player.addComponent<TransformComponent>(200.0, 700, 32, 32, 4);
    Player.addComponent<SpriteComponent>("player", true);
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(groupPlayers);
    SDL_Color white = {255, 255, 255, 255};
    label.addComponent<UILabel>(10, 10, "Test String", "arial", white);
    assets->CreateProjectile(Vector2D(100, 600), Vector2D(2, 1), 200, 1, "projectile");
    assets->CreateProjectile(Vector2D(50, 600), Vector2D(2, 1), 200, 1, "projectile");
    assets->CreateProjectile(Vector2D(10, 600), Vector2D(2, -1), 200, 1, "projectile");
    assets->CreateProjectile(Vector2D(0, 600), Vector2D(2, 1), 200, 1, "projectile");
    assets->CreateProjectile(Vector2D(20, 600), Vector2D(2, -1), 200, 1, "projectile");
}
auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));
auto &projectiles(manager.getGroup(Game::groupProjectiles));
void Game::Game ::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}
void Game ::update()
{
    SDL_Rect playerCol = Player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = Player.getComponent<TransformComponent>().position;
    std::stringstream ss;
    ss << "Player position: " << playerPos;
    label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

    manager.refresh();
    manager.update();
      onGround = false;
    for (auto &c : colliders)
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol))
        {
            if (cCol.y + cCol.h >= playerCol.y)
                onGround = true;
            cout << onGround << std::endl;
            Player.getComponent<TransformComponent>().position = playerPos;
            Player.getComponent<TransformComponent>().position.y -= (double)1;
            // Player.getComponent<TransformComponent>().position.x += (double)1;
        }
    }
    for (auto &p : projectiles)
    {
        if (Collision::AABB(Player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
        {
            std::cout << "Hit player!" << std::endl;
            p->destroy();
        }
    }
    camera.x = Player.getComponent<TransformComponent>().position.x - 200;
    camera.y = Player.getComponent<TransformComponent>().position.y - 160;
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
    for (auto &p : projectiles)
    {
        p->draw();
    }
    label.draw();
    SDL_RenderPresent(renderer);
}
void Game ::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
#endif