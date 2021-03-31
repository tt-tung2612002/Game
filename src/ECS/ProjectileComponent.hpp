#pragma once
#ifndef _PROJECTILECOMPONENT_HPP_
#define _PROJECTILECOMPONENT_HPP_
#include "ECS.hpp"
#include "Components.h"

class ProjectileComponent : public Component
{
public:
    ProjectileComponent(int range_, int speed_) : range(range_), speed(speed_) {}
    ~ProjectileComponent(){}
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }
    void update() override
    {
        distance += speed;
        if (distance > range)
        {
            entity->destroy();
        }
        else if (transform->position.x > Game::camera.x + Game::camera.w || transform->position.y > Game::camera.y + Game::camera.h || transform->position.x < Game::camera.x || transform->position.y < Game::camera.y)
        {
            entity->destroy();
        }
    }

private:
    TransformComponent *transform;
    int range = 0;
    int speed = 0;
    int distance = 0;
};
#endif