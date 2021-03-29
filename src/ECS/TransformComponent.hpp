#pragma once
#ifndef _TRANSFORMCOMPONENT_HPP_
#define _TRANSFORMCOMPONENT_HPP_
#include "../Vector2D.cpp"
#include "ECS.hpp"
class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;
    double height =32;
    double width =32;
    int scale = 1;
    int speed = 3;
    bool blocked = false;
    TransformComponent()
    {
        position.x = 0.0;
        position.y = 0.0;
    }
    TransformComponent(double x_, double y_)
    {
        position.x = x_;
        position.y = y_;
    }
    TransformComponent(int sc)
    {
        position.x = 0;
        position.y = 0;
        scale = sc;
    }
    TransformComponent(double x, double y, double h, double w, double sc)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }
    void init() override
    {
        velocity.x = 0;
        velocity.y = 0;
    }
    void update() override
    {
        position.x += static_cast<int>(velocity.x * speed);
		position.y += static_cast<int>(velocity.y * speed);
    }
};
#endif