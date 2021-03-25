#include "map.hpp"
#include "game.cpp"
#include <fstream>
#include "ECS/ECS.hpp"
#include "ECS/NewComponent.h"
static Manager manager;
Map::Map()
{
}
void Map::loadMap(std::string path, int sizeX, int sizeY)
{
    char tile;
    std::fstream mapFile;
    mapFile.open(path);
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile);
            //    Game::AddTile(static_cast<TileComponent::TileType>(atoi(&tile)),x*32,y*32);
            auto& temp(manager.addEntity());
            temp.addComponent<NewComponent>(x+32, y+32, 32, 32, static_cast<NewComponent::TileType>(atoi(&tile)));
            mapFile.ignore();
            break;
        }
        break;
    }

    mapFile.close();
}
