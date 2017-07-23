/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.h
 * Author: brian
 *
 * Created on July 23, 2017, 11:47 AM
 */

#include <json.hpp>
using json = nlohmann::json;

#ifndef MAP_H
#define MAP_H

// TODO: create TileSet, Map Class.  rename this to GameMapData?
class Map {
public:
    std::string tilesetName;
    std::string mapName;
    
    int tilesetColumns;
    int tilesetRows;
    int tilecount;
    
    int mapHeight;  // largest Height
    int mapWidth;   // largest Width
    std::vector<int> tiles;
    
public:
    Map();
    int getTile(int row, int col);
    int getClipX(int tileNum);
    int getClipY(int tileNum);
};

#endif /* MAP_H */

