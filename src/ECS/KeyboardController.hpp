#pragma once
#ifndef _KEYBOARDCONTROLLER_HPP_
#define _KEYBOARDCONTROLLER_HPP_
#include "../Game.hpp"
#include "ECS.hpp"
#include "Components.h"
extern bool onGround;
class KeyboardController : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
        sprite->Play("Idle");
    }
    void update() override
    {
        if (Game ::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                if (onGround == true)
                {
                    transform->velocity.y = transform->jumpHeight * -1;
                }
                else break;
                sprite->Play("Walk");     
                break;
            case SDLK_s:
                transform->velocity.y = 1;
                sprite->Play("Walk");
                break;
            case SDLK_a:
                transform->velocity.x = -1;
                sprite->Play("Walk");
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_d:
                transform->velocity.x = 1;
                sprite->Play("Walk");
                break;
            default:
                break;
            }
        }
        if (Game ::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = 0;
                sprite->Play("Idle");

                break;
            case SDLK_s:
                transform->velocity.y = 0;
                sprite->Play("Idle");
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                sprite->Play("Idle");
                sprite->spriteFlip = SDL_FLIP_NONE;
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                sprite->Play("Idle");
                break;
            case SDLK_ESCAPE:
                Game::isRunning = false;
                break;
            default:
                break;
            }
        }
            if (onGround == false)
        {
            transform->velocity.y += transform->accelGravity;
            if (transform->velocity.y > transform->maxGravity)
                transform->velocity.y = transform->maxGravity;
        }
    }
};
#endif