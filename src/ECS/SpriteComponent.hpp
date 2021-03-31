#pragma once
#ifndef _SPRITECOMPONENT_HPP_
#define _SPRITECOMPONENT_HPP_
#include "Components.h"
#include "../TextureManager.h"
#include "SDL2/SDL.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.hpp"
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
    }
    SpriteComponent(std:: string id,bool isAnimated)
    {
        
        animated = isAnimated;
        Animation idle = Animation(0,3,100);
        Animation walk = Animation(1,8,100); 
        animations.emplace("Idle",idle);
        animations.emplace("Walk",walk);
        Play("idle");
        setTexture(id);
    }
    SpriteComponent(const char *path)
    {
        TextureManager::LoadTexture(path);
    }
    void setTexture(std ::string path)
    {
        texture = Game::assets->GetTexture(path);
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
        destRect.w = transform->width * transform->scale ;
        destRect.h = transform->height * transform->scale ;
    }
    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }
    void Play(const char* animName)
    {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};
#endif