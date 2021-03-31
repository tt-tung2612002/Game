#pragma once
#ifndef _COLLISION_HPP_
#define _COLLISION_HPP_
#include "SDL2/SDL.h"
class ColliderComponent;

class Collision
{
public:
    static bool AABB(const SDL_Rect &recA, const SDL_Rect &recB);
    static bool AABB(const ColliderComponent &colA, const ColliderComponent &colB);
};
#endif