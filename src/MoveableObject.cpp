/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MoveableObject.cpp
 * Author: brian
 * 
 * Created on January 6, 2016, 6:13 PM
 */
#include "App.h"
#include "MoveableObject.h"

MoveableObject::MoveableObject( ) {
    mPosX = 0;//SCREEN_WIDTH / 2;
    mPosY = 0;//SCREEN_HEIGHT / 2;
    
    mCollider.x = mPosX;
    mCollider.y = mPosY;

    mVelX = 0;
    mVelY = 0;

    mFaceDirection = 0.0;
    mMoveDirection = 0.0;

    mSpriteName = "";
}

MoveableObject::MoveableObject( const MoveableObject& orig ) {
}

MoveableObject::~MoveableObject( ) {
}

bool MoveableObject::move( ) {
    //Move the dot left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    std::cout << mVelX << "_" << mPosX << " " << getWidth() << " " << mPosX+getWidth() << " " << SCREEN_WIDTH << std::endl;
    //If the dot went too far to the left or right
    if ( (mPosX < 0) || (mPosX + getWidth() > App::GetWindowWidth()) ) {
        //move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }

    //Move the dot up or down
    mPosY += mVelY;
    mCollider.y = mPosY;

    //If the dot went too far up or down
    if ( (mPosY < 0) || (mPosY + getHeight() > App::GetWindowHeight()) ) {
        //move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }

    //std::cout << "x: " << x << ", y: " << y << std::endl;
    
    return false;
}

int MoveableObject::getHeight() {
    return mHeight;
}

int MoveableObject:: getWidth() {
    return mWidth;
}

void MoveableObject::setHeight(int _height) {
    mHeight = _height;
    
    mCollider.h = mHeight;
}

void MoveableObject::setWidth(int _width) {
    mWidth = _width;
    mCollider.w = mWidth;
}

SDL_Rect MoveableObject::getCollider() {
    return mCollider;
}

bool MoveableObject::checkCollision( SDL_Rect targetRect ) {
    SDL_Rect result;
    SDL_bool val;
    val = SDL_IntersectRect( &mCollider, &targetRect, &result );
    
    return val;
}

std::string MoveableObject::getSpriteName() {
    return mSpriteName;
}