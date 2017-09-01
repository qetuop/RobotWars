/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sprite.h
 * Author: brian
 *
 * Created on August 5, 2017, 6:18 PM
 */

#include "SDL2/SDL.h"

#ifndef SPRITE_H
#define SPRITE_H

#ifdef __cplusplus
extern "C" {
#endif

class Sprite {
private:
    
    // coordX * tileWidth = pixel X
    int coordX;  
    int coordY;
    
    // pixels
    int posX;
    int posY;
    
    // pixels
    int width;
    int height;
           
    SDL_Rect hitBox; // for combat collisions
    SDL_Rect collider; // just for env collisions
    SDL_Rect bounder; // full bounding box
        
public:
    
    Sprite();
    
    int getHeight();
    int getWidth();    
    void setHeight(int _height);
    void setWidth(int _width);
    
    int getCoordX();
    int getCoordY();
    void setCoordX(int x);
    void setCoordY(int y);
    
    int getPosX();
    int getPosY();
    void setPosX(int x);
    void setPosY(int y);
    
    SDL_Rect* getBounder();
    
    // ?? render(??)  or  Texture* getTexture(??)
    // update()  --> only those sprites in the camera view will need to?

}; // Sprite
    
    
#ifdef __cplusplus
}
#endif
    
#endif /* SPRITE_H */

