#include "map.hpp"
#include "game.cpp"
#include <fstream>
#include "ECS/ECS.hpp"
#include "ECS/NewComponent.h"
static Manager manager;
const char* mapfile = "terrain.png";
enum groupLabels : std::size_t
{
    groupMap,groupPlayers,groupEnemies,groupColliders
};
Map::Map()
{
}
void Map::loadMap(std::string path, int sizeX, int sizeY)
{
    char tile;
    std::fstream mapFile;
    mapFile.open(path);
    int srcX,srcY;
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile);
            srcY = atoi(&tile)*32;
            mapFile.get(tile);
            srcX = atoi(&tile)*32;
            auto& temp(manager.addEntity());
            temp.addComponent<NewComponent>(srcX,srcY,x*64,y*64,mapfile);
            temp.addGroup(groupLabels :: groupMap);
            mapFile.ignore();
        }
    }
    mapFile.close();
}
