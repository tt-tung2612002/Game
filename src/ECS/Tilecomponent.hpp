#pragma once
#ifndef _TILECOMPONENT_HPP_
#define _TILECOMPONENT_HPP_
#include "ECS.hpp"
#include "../Vector2D.hpp"
#include "../game.hpp"
#include "../TextureManager.h"

class TileComponent : public Component
{
public:
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
    TileComponent()
    {
        SDL_DestroyTexture(texture);
    }
    TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id)
    {
        texture = Game::assets->GetTexture(id);
        position.x = xpos;
        position.y = ypos;
        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize;
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = tsize * tscale;
    }
    void update() override
    {
        destRect.x = static_cast<int>(position.x - Game::camera.x);
        destRect.y = static_cast<int>(position.y - Game::camera.y);
    }
    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};
#endif