#pragma once
#include <cstring>
#include <string>
#include "Game.hpp"

class Map
{
public:
    Map(const char *mfp, int ms, int ts);
    ~Map();
    void loadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xpos, int ypos);

    
private:
    const char *mapFilePath;
    int mapScale;
    int tileSize;
    int scaledSize;
};