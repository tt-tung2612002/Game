#pragma once
#include <cstring>
#include <string>
#include "Game.hpp"

class Map{
public: 
    Map();
    ~Map();
    static void loadMap(std:: string path, int sizeX,int sizeY);
private:
  
};