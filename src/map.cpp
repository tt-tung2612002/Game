#pragma once
#include "Map.hpp"
#include "Game.hpp"
#include <fstream>
#include "ECS\ECS.hpp"
#include "ECS\Components.h"
using namespace std;
extern Manager manager;

const char *mapfile = "testbackground.png";
Map::Map()
{
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
            // srcY = atoi(&tile) * 32;
            // mapFile.get(tile);
            // srcX = atoi(&tile) * 32;
            srcY = (n / 10)*32;
            cout << srcY << endl;
            srcX = ((n % 10))*32;
            cout << srcX<< endl;
            auto &temp(manager.addEntity());
            temp.addComponent<TileComponent>(srcX, srcY , x * 64, y * 64, mapfile);
            temp.addGroup(Game::groupMap);
        }
    }
    mapFile.close();
}
