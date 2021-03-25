#pragma once
#ifndef _SPRITECOMPONENT_HPP_
#define _SPRITECOMPONENT_HPP_
#include "Components.h"
#include "SDL2/SDL.h"
class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

public:
    SpriteComponent() = default;
    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }
    SpriteComponent(const char *path)
    {
        SDL_Surface *tempSurface = IMG_Load(path);
        texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
    }
    void setTexture(const char *path)
    {
        SDL_Surface *tempSurface = IMG_Load(path);
        texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
    }
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.h = transform->height;
        srcRect.w = transform->width;
    }
    void update() override
    {
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
        if (transform->width > 500 || transform->height > 500)
        {
            destRect.w = (transform->width) / 30 * transform->scale;
            destRect.h = (transform->height) / 30 * transform->scale;
        }
        else
        {
            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;
        }
    }
    void draw() override
    {
        SDL_RenderCopy(Game::renderer,texture,&srcRect,&destRect);
    }
};
#endif