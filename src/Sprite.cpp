/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sprite.h"

Sprite::Sprite() {
    coordX = 0; 
    coordY = 0;        
    
    // pixels
    int width = 0;
    int height = 0;
    
    posX = coordX * width;
    posY = coordY * height;
}

int Sprite::getHeight() {
    return height;
}

int Sprite:: getWidth() {
    return width;
}

void Sprite::setHeight(int _height) {
    height = _height;   
    bounder.h = _height;
}

void Sprite::setWidth(int _width) {
    width = _width;
    bounder.w = _width;
}

int Sprite::getCoordX() {
    return coordX;
}

int Sprite::getCoordY() {
    return coordY;
}

void Sprite::setCoordX(int x) {
    coordX    = x;
    posX      = coordX * width;
    bounder.x = posX;
}

void Sprite::setCoordY(int y) {
    coordY    = y;
    posY      = coordY * height;
    bounder.y = posY;    
}


int Sprite::getPosX() {
    return posX;
}

int Sprite::getPosY() {
    return posY;
}

void Sprite::setPosX(int x) {
    posX    = x;
    // shoud i set coord from pos? coordX = math.round(posX / width);
    bounder.x = posX;
}

void Sprite::setPosY(int y) {
    posY    = y;
    //posY      = coordY * height;
    bounder.y = posY;    
}

SDL_Rect* Sprite::getBounder() {
    return &bounder;
}