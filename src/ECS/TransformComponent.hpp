#pragma once
#ifndef _TRANSFORMCOMPONENT_HPP_
#define _TRANSFORMCOMPONENT_HPP_
#include "Components.h"
#include "../Vector2D.hpp"
extern bool onGround;
class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;
    int jumpHeight = 5;
    double height = 32;
    double width = 32;
    static const double constexpr accelGravity =1.0;
    static const double constexpr maxGravity = 5.0;
    int scale = 1;
    int speed = 3;
    TransformComponent()
    {
        position.x = 420;
        position.y = 600;
    }
    TransformComponent(double x_, double y_)
    {
        position.x = x_;
        position.y = y_;
    }
    TransformComponent(int sc)
    {
        position.x = 420;
        position.y = 600;
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