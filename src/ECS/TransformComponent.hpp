#pragma once
#include "../Vector2D.cpp"

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;
    double height;
    double width;
    int scale = 1;
    int speed = 3;

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
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};