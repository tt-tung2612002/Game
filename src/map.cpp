// #include "map.hpp"
// #include "application.hpp"
// #include "ECS/TextureManager.hpp"
// #include <fstream>

// Map::Map()
// {
// }
// void Map::loadMap(std:: string path, int sizeX,int sizeY)
// {
//     char tile;
//     std:: fstream mapFile;
//     mapFile.open(path);
//     for (int y =0;y< sizeY;y++){
//        for (int x = 0; x < sizeX; x++){
//            mapFile.get(tile);
//            Application::AddTile(static_cast<TileComponent::TileType>(atoi(&tile)),x*32,y*32);
//            mapFile.ignore();
//         }
//     }

//     mapFile.close(); 
// }

