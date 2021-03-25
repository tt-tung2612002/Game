#pragma once
#ifndef _SPRITECOMPONENT_HPP_
#define _SPRITECOMPONENT_HPP_
#include "Components.h"
#include "SDL2/SDL.h"
#include "Animation.h"
#include <map>
class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    bool animated = false;
    int frames = 0;
    int speed = 100;

public:
    int animIndex = 0;
    std:: map<const char*, Animation> animations;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    SpriteComponent() = default;
    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }
    SpriteComponent(const char *path,bool isAnimated)
    {
        
        animated = isAnimated;
        Animation idle = Animation(0,3,100);
        Animation walk = Animation(1,8,100); 
        animations.emplace("Idle",idle);
        animations.emplace("Walk",walk);
        Play("idle");
        SDL_Surface *tempSurface = IMG_Load(path);
        texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
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
        if (animated)
        {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }
        srcRect.y = animIndex * transform->height;
        destRect.x = static_cast<int> (transform->position.x) - Game::camera.x;
        destRect.y = static_cast<int> (transform->position.y) - Game::camera.y;
        if (transform->width > 500 || transform->height > 500)
        {
            destRect.w = (transform->width) / 30 * transform->scale;
            destRect.h = (transform->height) / 30 * transform->scale;
        }
        else
        {
            destRect.w = transform->width * transform->scale + 100;
            destRect.h = transform->height * transform->scale + 100;
        }
    }
    void draw() override
    {
        SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &destRect,NULL,NULL,spriteFlip);
    }
    void Play(const char* animName)
    {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};
#endif