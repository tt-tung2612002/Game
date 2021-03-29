#pragma once
#include "Map.hpp"
#include "Game.hpp"
#include <fstream>
#include "ECS\ECS.hpp"
#include "ECS\Components.h"

extern Manager manager;

const char *mapfile = "terrain.png";
Map::Map()
{
}
void Map::loadMap(std::string path, int sizeX, int sizeY)
{
    char tile;
    std::fstream mapFile;
    mapFile.open(path);
    int srcX, srcY;
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile);
            srcY = atoi(&tile) * 32;
            mapFile.get(tile);
            srcX = atoi(&tile) * 32;
            auto &temp(manager.addEntity());
            temp.addComponent<TileComponent>(srcX, srcY, x * 64, y * 64, mapfile);
            temp.addGroup(Game::groupMap);
            mapFile.ignore();
        }
    }
    mapFile.close();
}
