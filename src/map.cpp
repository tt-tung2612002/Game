#pragma once
#include "Map.hpp"
#include "Game.hpp"
#include <fstream>
#include "ECS\ECS.hpp"
#include "ECS\Components.h"
using namespace std;
extern Manager manager;

const char *mapfile = "testbackground.png";
Map::Map(const char *mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts)
{
    scaledSize = ms * ts;
}
int srcX, srcY;
void convertToMatrix(string &s, int &srcX, int &srcY)
{
    int n = stoi(s);
    srcX = n / 10;
    srcY = n % 10 - 1;
}
void Map::loadMap(std::string path, int sizeX, int sizeY)
{

    std::fstream mapFile;
    mapFile.open(path);

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            int n;
            mapFile >> n;
            n--;
            srcY = (n / 10) * 32;
            srcX = ((n % 10)) * 32;
            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
        }
    }
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            int n;
            mapFile >> n;
            if (n==1)
            {
                auto &tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(Game::groupColliders);
                // mapFile.ignore();
            }
        }
    }
    mapFile.close();
}
void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto &temp(manager.addEntity());
    temp.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
    temp.addGroup(Game::groupMap);
}