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

Bullet::Bullet(int _x, int _y, double _direction, std::string name) {
    mPosX = _x;
    mPosY = _y;

    mFaceDirection = (int)_direction;

    mVelX = BULLET_RATE * cos(mFaceDirection * M_PI / 180);
    mVelY = BULLET_RATE * sin(mFaceDirection * M_PI / 180);
    
    mSpriteName = name;
    
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
    mBounder.x = mPosX;
    
    mPosY += mVelY;
    mBounder.y = mPosY;

    //std::cout << "Bullet::move::x = " << mPosX << ", y = " << mPosY << std::endl;

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

void Bullet::render(SDL_Renderer* Renderer) {
        Texture *texture = TextureBank::Get(mSpriteName);
               
        SDL_Rect clip;
        clip.x = clip.y = 0;
        clip.h = clip.w = 32;
        
        if ( mSpriteName == "laser" ) {
            int mod = 8;
            //clip.h*=mod;
            clip.w*=mod;
            //mPosX/=mod/2;
            //mPosY/=mod/2;
//            if ( mFaceDirection == 0 || mFaceDirection == 180 ) {
//                clip.w = 128;
//            }
//            else clip.h = 128;
        }
        
        //double filp = 0;
       
        // render(SDL_Renderer *renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
            
        SDL_Point center;
        center.x = mPosX+16;
        center.y = mPosY+16;
//        std::cout << "BULLET " << mPosX << " " << mPosY 
//               << ", clip: " << clip.x << " " << clip.y << " " << clip.w << " " << clip.h
//               << ", center: " << center.x << " " << center.y
//               << std::endl;
        
        double flip = 0;
        //legTx->render(Renderer, getPosX(), getPosY(), &clip, filp);
        //texture->render(Renderer, mPosX, mPosY, &clip, mFaceDirection, &center);  // center screws things up???
        texture->render(Renderer, mPosX, mPosY, &clip, mFaceDirection);
        //texture->Render(mPosX, mPosY, 64,64);
        
        //Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight)
        //texture->Render(mPosX, mPosY, clip.w, clip.h, 0, 0, 32,32);
    }

