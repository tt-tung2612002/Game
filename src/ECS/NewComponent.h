#pragma once 

#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
class NewComponent : public Component
{
public:
    enum class TileType{blank,water,dirt,grass};
    TransformComponent *transform;
    SpriteComponent *sprite;
    SDL_Rect tileRect;
    const char* path;
    TileType tileID;
    NewComponent() = default;
    NewComponent(int x, int y, int w, int h,TileType id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;
        switch (id)
        {
        case TileType::water:
            path = "water.png";
            break;
        case TileType::dirt:
            path = "dirt.png";
            break;
        case TileType::grass:
            path = "grass.png";
            break;
        default:
            break;
        }
    }
    void init() override
    {
        entity->addComponent<TransformComponent>((double)tileRect.x,(double) tileRect.y, tileRect.w, tileRect.h, 1);
        transform = &entity->getComponent<TransformComponent>();
        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
};