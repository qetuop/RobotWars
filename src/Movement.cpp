/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Movement.h"
#include "App.h"

bool Movement::move(int *posX, int *posY, SDL_Rect *bounder) {
    
    // Move left or right
    *posX += velX;
    bounder->x = *posX; 

    // TODO: what should be the bounds check, the application size, the camera, level, etc
    // went too far to the left or right
    if ( (*posX < 0) || (*posX + bounder->w > App::GetWindowWidth()) ) {
        //move back
        *posX -= velX;
        bounder->x = *posX;
    }

    // Move up or down
    *posY += velY;
    bounder->y = *posY;

    // went too far up or down
    if ( (*posY < 0) || (*posY + bounder->h > App::GetWindowHeight()) ) {
        //move back
        *posY -= velY;
        bounder->y = *posY;
    }
    
    return false;
}

int Movement::getVelX() {
    return velX;
}
void Movement::setVelX(int i) {
    velX = i;
}

int Movement::getVelY() {
    return velY;
}

void Movement::setVelY(int i) {
    velY = i;
}
    
double Movement::getFaceDirection() {
    return faceDirection;
}

void Movement::setFaceDirection(double d) {
    faceDirection = d;
}

double Movement::getMoveDirection() {
    return moveDirection;
}

void Movement::setMoveDirection(double d) {
    moveDirection = d;
}