#ifndef _COLLIDERCOMPONENT_HPP_
#define _COLLIDERCOMPONENT_HPP_
class ColliderComponent;
// std::vector< ColliderComponent * >colliders;
#include <string>
#include "SDL2/sdl.h"
#include "TransformComponent.hpp"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std :: string tag;
    SDL_Texture *tex;
    SDL_Rect srcR,destR;

    TransformComponent* transform;
    ColliderComponent(std:: string s){
        tag = s;
    }
    void init() override{
        if(!entity->hasComponent<TransformComponent>()){
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
        Game::colliders.push_back(this);
    }
    void update() override{
        collider.x = static_cast<int> (transform->position.x);
        collider.y = static_cast<int> (transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }
};

#endif