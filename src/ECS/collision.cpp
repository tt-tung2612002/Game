#include "Collision.hpp"
#include "ColliderComponent.hpp"
bool Collision::AABB(const SDL_Rect& recA,const SDL_Rect& recB)
{
    if(recA.x + recA.w >= recB.x +1 and recB.x + recB.w >= recA.x +1 && recA.y + recA.h >= recB.y +1 && recB.y + recB.h >= recA.y +1)
        return true;
    return false;
}
bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB){
    if (AABB(colA.collider,colB.collider)) {
        std::cout << colA.tag  << "hit: " << colB.tag << std::endl;
        return true;
    }
    return false;
}