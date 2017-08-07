/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Movement.h
 * Author: brian
 *
 * Created on August 6, 2017, 12:39 PM
 */

#include "SDL2/SDL.h"

#ifndef MOVEMENT_H
#define MOVEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

class Movement {
private:
    // The velocity
    int velX;
    int velY;

    // facing
    double faceDirection;
    
    // moving
    double moveDirection;
    
public:
    bool move(int *posX, int *posY, SDL_Rect *bounder);
    
}; // Movement
    
    
#ifdef __cplusplus
}
#endif

#endif /* MOVEMENT_H */

