/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bullet.cpp
 * Author: brian
 * 
 * Created on January 2, 2016, 7:34 PM
 */

#include "Bullet.h"
#include "App.h"

#include <iostream>


Bullet::Bullet() {
    // do once
    mVelX = BULLET_RATE * cos(mFaceDirection);
    mVelY = BULLET_RATE * sin(mFaceDirection);
}

Bullet::Bullet(int _x, int _y, double _direction) {
    mPosX = _x;
    mPosY = _y;

    mFaceDirection = (int)_direction;

    mVelX = BULLET_RATE * cos(mFaceDirection * M_PI / 180);
    mVelY = BULLET_RATE * sin(mFaceDirection * M_PI / 180);
    
//     std::cout << "Bullet(): x = " << x 
//             << ", y = " << y
//             << ", direction = " << direction
//             << ", xVel = " << xVel
//             << ", yVel = " << yVel
//             << std::endl;
     
}

Bullet::~Bullet() {
    //std::cout << "~Bullet()" << std::endl;
}

bool Bullet::move() {
    bool isAlive = true;
    
    mPosX += mVelX;
    mCollider.x = mPosX;
    
    mPosY += mVelY;
    mCollider.y = mPosY;

    //std::cout << "Bullet::move::x = " << x << ", y = " << y << std::endl;

    // hits a wall
    if ((mPosX <= 0) || (mPosX >= App::GetWindowWidth())) {
        isAlive = false;
    } else if ((mPosY <= 0) || (mPosY >= App::GetWindowHeight())) {
        isAlive = false;
    }
    
    // should this be in the stuck objects logic?
//    if ( checkCollision(App::GetInstance()->mNPCPtr->getCollider())) {
//        std::cout << "BULLET HIT BADDIE" << std::endl;
//        App::GetInstance()->mNPCPtr->hit();
//    }

    return isAlive;

} // move

