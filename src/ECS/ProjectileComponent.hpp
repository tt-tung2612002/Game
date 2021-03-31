#pragma once
#ifndef _PROJECTILECOMPONENT_HPP_
#define _PROJECTILECOMPONENT_HPP_
#include "ECS.hpp"
#include "../Vector2D.hpp"
#include "Components.h"
using namespace std;
class ProjectileComponent : public Component
{
public:
    ProjectileComponent(int range_, int speed_,Vector2D velocity_) : range(range_), speed(speed_), velocity(velocity_) {}
    ~ProjectileComponent(){}
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        transform->velocity = velocity;
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
    Vector2D velocity;
};
#endif