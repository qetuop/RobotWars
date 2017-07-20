/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MoveableObject.h
 * Author: brian
 *
 * Created on January 5, 2016, 7:10 PM
 */
#include "SDL2/SDL.h"

#include <iostream>

#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H

class MoveableObject {
                            
public:
    // sprite bounding box
    int mHeight;
    int mWidth;
    
    // TODO: make a setX/Y func?

    // the offsets
    int mPosX;
    int mPosY;

    // The velocity
    int mVelX;
    int mVelY;

    // facing
    double mFaceDirection;
    
    // moving
    double mMoveDirection;

    std::string mSpriteName;

    // collision box
    SDL_Rect mCollider;
    
//    int WALKING_ANIMATION_FRAMES = 3;
//    SDL_Rect gSpriteClips[4][WALKING_ANIMATION_FRAMES];
//    LTexture gSpriteSheetTexture;
    
public:
    MoveableObject();
    MoveableObject( const MoveableObject& orig );
    ~MoveableObject();
    
    // return true if collision detected - not impltmented here yet,
    virtual bool move();
    
    int getHeight();
    int getWidth();
    
    void setHeight(int _height);
    void setWidth(int _width);
    
    SDL_Rect getCollider();
    
    bool checkCollision( SDL_Rect targetRect );
    
    // TODO: tmp - need to figure out if tex ref should be stored in class or just the name
    virtual std::string getSpriteName();
    
}; // class MoveableObject

#endif /* MOVEABLEOBJECT_H */

