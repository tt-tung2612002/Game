#ifndef _TILECOMPONENT_HPP_
#define _TILECOMPONENT_HPP_
// #include "SpriteComponent.hpp"
#include "ECS.hpp"
#include "TransformComponent.hpp"
// #include "SDL2/SDL.h"
// #include "SpriteComponent.hpp"
class TileComponent : public Component
{
public:
    enum class TileType{water,dirt,grass};
    TransformComponent *transform;
    // SpriteComponent *sprite;
    SDL_Rect tileRect;
    const char* path;
    TileType tileID;
    TileComponent() = default;
    TileComponent(int x, int y, int w, int h,TileType id)
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
        // entity->addComponent<SpriteComponent>(path);
        // sprite = &entity->getComponent<SpriteComponent>();
    }
};
#endif