/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MapUtil.h"
#include <fstream>
#include <math.h>

MapUtil::MapUtil() {
    tilesetName = "/home/brian/NetBeansProjects/SDL/RobotWars/Resources/robot_wars_tileset.json";
    mapName = "/home/brian/NetBeansProjects/SDL/RobotWars/Resources/robot_wars_map.json";
            
    // TILESET
    std::ifstream tileset (tilesetName, std::ifstream::in);
    json tilesetJson;
    tileset >> tilesetJson;
    tilesetColumns = tilesetJson["columns"].get<int>();
    tilecount = tilesetJson["tilecount"].get<int>();
    tilesetRows = ceil(tilecount / tilesetColumns);
    //std::cout << tilesetColumns << " " << tilesetRows << " " << tilecount << std::endl;
    
    // MAP
    std::ifstream map (mapName, std::ifstream::in);
    json mapJson;
    map >> mapJson;
    mapHeight = mapJson["height"].get<int>();
    mapWidth = mapJson["width"].get<int>();
    tiles = mapJson["layers"][0]["data"].get<std::vector<int>>();
    
   // std::cout << mapWidth << " " << mapHeight << " " << tiles.size() << std::endl;        

} // CTOR

int MapUtil::getTile(int row, int col) {
    // 4x8 grid
    // i = row * 4 + col
    int index = row * mapWidth + col;
    return tiles[index] -1;  // TODO: change to something using firstgid?
}

int MapUtil::getClipX(int tileNum) {
    return tileNum % tilesetColumns;    // % is the "modulo operator", the remainder of i / width;
}

int MapUtil::getClipY(int tileNum) {
    return tileNum / tilesetColumns;    // % is the "modulo operator", the remainder of i / width;
}
