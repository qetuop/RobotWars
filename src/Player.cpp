/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Player.h"
#include "App.h"

#include <iostream>


//static int doOnce = 1;
const int FRAME_COUNT = 3;
const int SPEED = 8;

Player::Player( ) {
    std::cout << "Player created " << std::endl;

    frame = 0;
    mSpriteName = "somecharacters" ;
}

Player::~Player( ) {
    std::cout << "Player destroyed" << std::endl;
}


void Player::handle_input( SDL_GameController *controller ) {
    
    // TODO: need an update() type function
    
    

    // DPAD
    bool Up = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
    bool Down = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    bool Left = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    bool Right = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

    bool Start = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
    bool Back = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK);

    bool LeftShoulder = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
    bool RightShoulder = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

    bool AButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
    bool BButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
    bool XButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X);
    bool YButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);

    Sint16 StickLeftX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
    Sint16 StickLeftY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);

    Sint16 StickRightX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
    Sint16 StickRightY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);

    //          -90
    //     -135  |  -45
    //         \ | /
    //    180 -- + --  0
    //         / | \
    //     135   |  45
    //          90
    //direction = atan2((double) yDir, (double) xDir) * (180.0 / M_PI);

    if ( ((StickRightX < -JOYSTICK_DEAD_ZONE) || (StickRightX > JOYSTICK_DEAD_ZONE)) || 
         ((StickRightY < -JOYSTICK_DEAD_ZONE) || (StickRightY > JOYSTICK_DEAD_ZONE)) ) {
        mFaceDirection = atan2((double) StickRightY, (double) StickRightX) * (180.0 / M_PI);
        
        
        if      ( mFaceDirection > -45 && mFaceDirection < 45 ) mFaceDirection = 0;
        else if ( mFaceDirection > -135 && mFaceDirection < -45 ) mFaceDirection = -90;
        else if ( mFaceDirection > 135 || mFaceDirection < -135 ) mFaceDirection = 180;
        else if ( mFaceDirection > 45 && mFaceDirection < 135 ) mFaceDirection = 90;
        
        std::cout << "mFaceDirection:  " << mFaceDirection << std::endl;
        
        //fireBullet();
    }

    //std::cout << "direction " << int(direction) << std::endl;

    //if ( doOnce ){   
    //    std::vector<int> test = {0, 45, 90, 135, 180, -135, -90, -45};
    //    for (auto b : test) {
    //        auto bullet = std::make_shared<Bullet>(x, y, b);
    //        mBullets.push_back(bullet);
    //    }
    //    doOnce = 0;
    //}

    if ( RightShoulder == 1 ) {
//        fireBullet();
    }

    // ------------------
    // Player movement
    //-------------------

    if ( ((StickLeftX < -JOYSTICK_DEAD_ZONE) || (StickLeftX > JOYSTICK_DEAD_ZONE)) || 
         ((StickLeftY < -JOYSTICK_DEAD_ZONE) || (StickLeftY > JOYSTICK_DEAD_ZONE)) ) {
        mMoveDirection = atan2((double) StickLeftY, (double) StickLeftX) * (180.0 / M_PI);
        
        if      ( mMoveDirection > -45 && mMoveDirection < 45 ) mMoveDirection = 0;
        else if ( mMoveDirection > -135 && mMoveDirection < -45 ) mMoveDirection = -90;
        else if ( mMoveDirection > 135 || mMoveDirection < -135 ) mMoveDirection = 180;
        else if ( mMoveDirection > 45 && mMoveDirection < 135 ) mMoveDirection = 90;
        
        std::cout << "mMoveDirection:  " << mMoveDirection << std::endl;
        //fireBullet();
    }
    
    // If the X axis is neutral
    if ( (StickLeftX > -JOYSTICK_DEAD_ZONE) && (StickLeftX < JOYSTICK_DEAD_ZONE) ) {
        mVelX = 0;
    }// Adjust the velocity
    else {
        if ( StickLeftX < 0 ) {
            mVelX = -getWidth() / SPEED;
        } else {
            mVelX = getWidth() / SPEED;
        }
    }

    // If the Y axis is neutral
    if ( (StickLeftY > -JOYSTICK_DEAD_ZONE) && (StickLeftY < JOYSTICK_DEAD_ZONE) ) {
        mVelY = 0;
    }// Adjust the velocity
    else {
        if ( StickLeftY < 0 ) {
            mVelY = -getHeight() / SPEED;
        } else {
            mVelY = getHeight() / SPEED;
        }
    }

    //std::cout << "xVel: " << xVel << ", yVel: " << yVel << ", direction: " << direction << std::endl;
} // handle_input

    //          -90
    //     -135  |  -45
    //         \ | /
    //    180 -- + --  0
    //         / | \
    //     135   |  45
    //          90

    SDL_Rect Player::getClip() {
        SDL_Rect clip;
        
        // frame 
        clip.x = frame*32;
        //std::cout << "FRAME= " << frame << std::endl;
        
        // mMoveDirection
        int y = 0;
        switch ( (int)mMoveDirection ) {
            case 0:
                y = 64;
                break;
                
           case 90:
                y = 0;
                break;
                
            case -90:
                y = 96;
                break;
                
            case 180:
                y = 32;
                break;
        }
        clip.y = y;
        
        clip.h=32;
        clip.w=32;
        
        // mFaceDirection
        
        return clip;
    }

std::string Player::getSpriteName() {
    return mSpriteName;// + std::to_string(frame);
}

bool Player::move() {
    MoveableObject::move();
    
    // TODO: better way
    if ( mVelX != 0 || mVelY != 0) {
        frame = ++frame % FRAME_COUNT;
//        ++frame;
//        if ( frame / 3 >= FRAME_COUNT*2 ) {
//            frame = 0;
//        }
    }
    
    return false;
}