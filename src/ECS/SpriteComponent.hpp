#include "Components.hpp"
#include "SDL2/SDL.h"
#include "TextureManager.cpp"
#include "../Vector2D.hpp"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

public:
    SpriteComponent() = default;
    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }
    SpriteComponent(const char *path)
    {
        texture = TextureManager::loadTexture(path);
    }
    void setTexture(const char *path)
    {
        texture = TextureManager::loadTexture(path);
    }
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.h = transform->height;
        srcRect.w = transform->width;
    }
    void update() override
    {
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }
    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }
};