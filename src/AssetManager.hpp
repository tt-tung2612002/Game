#pragma once
#ifndef _ASSETMANAGER_HPP_
#define _ASSETMANAGER_HPP_
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.hpp"
#include "ECS/ECS.hpp"

class AssetManager
{
public:
    AssetManager(Manager *man);
    ~AssetManager();
    void CreateProjectile(Vector2D pos,int range,int speed, std:: string id);
    void AddTexture(std:: string id, const char* path);
    SDL_Texture* GetTexture(std:: string id);
private:
    Manager* manager;
    std:: map<std::string,SDL_Texture*> textures;
};
#endif