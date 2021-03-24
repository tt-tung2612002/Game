#include "application.hpp"
#include "ECS/TextureManager.hpp"
#include "ECS/Components.hpp"
#include "ECS/Collision.cpp"
Manager manager;
SDL_Renderer* Application::renderer = nullptr;
SDL_Event Application::event;
// std:: vector<ColliderComponent*> Application:: colliders;
Entity &Player(manager.addEntity());
Entity &Player2(manager.addEntity());
auto &wall(manager.addEntity());
// auto &tile(manager.addEntity());
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
    Player.addComponent<TransformComponent>(0,0,200,200,1);
    Player.addComponent<SpriteComponent>("cute.png");
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
    Player2.addComponent<TransformComponent>(200,0,200,200,1);
    Player2.addComponent<SpriteComponent>("cute.png");
    Player2.addComponent<KeyboardController>();
    Player2.addComponent<ColliderComponent>("player");
    wall.addComponent<TransformComponent>(500,300,100,100,1);
    wall.addComponent<SpriteComponent>("blue.png");
    wall.addComponent<ColliderComponent>("wall");
    wall.addComponent<KeyboardController>();
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
    if (Collision::AABB(Player.getComponent<ColliderComponent>().collider,wall.getComponent<ColliderComponent>().collider)){
        Player.getComponent<TransformComponent>().velocity * -1;
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
