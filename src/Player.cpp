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
const int SPEED = 16;

Player::Player( ) {
    std::cout << "Player created " << std::endl;

    frame = 0;
    //mSpriteName = "somecharacters" ;

    head = "head";
    torso = "torso";
    leftArm = "left_arm";
    rightArm = "right_arm";
    leg = "leg";

    firing = false;
}

Player::~Player( ) {
    std::cout << "Player destroyed" << std::endl;
}

void Player::handle_input( ) {
    // TODO: need an update() type function
    double faceDir = 0.0;
    double moveDir = 0.0;
    int velX = 0;
    int velY = 0;

    // ------------------
    // Player Facing
    //-------------------
    int x, y;
    SDL_GetMouseState(&x, &y);

    //std::cout << "(x,y)=(" << x << "," << y << ")" << std::endl;
    //std::cout << "coord(x,y)=(" << this->getCoordX() << "," << this->getCoordY() << ")" << std::endl;
    //std::cout << "pos(x,y)=(" << this->getPosX() << "," << this->getPosY() << ")" << std::endl;

    int centerX = this->getPosX() + (getWidth() / 2);
    int centerY = this->getPosY() + (getHeight() / 2);

    faceDir = atan2((double)(y-centerY), (double)(x-centerX)) * (180.0 / M_PI);
    //std::cout << "facedir1= " << faceDir << std::endl;

    if ( faceDir > -45 && faceDir < 45 ) faceDir = 0;
    else if ( faceDir > -135 && faceDir < -45 ) faceDir = -90;
    else if ( faceDir > 135 || faceDir < -135 ) faceDir = 180;
    else if ( faceDir > 45 && faceDir < 135 ) faceDir = 90;
    //std::cout <<"facedir2= " << faceDir << std::endl;

    // ------------------
    // Player Movement / Velocity
    //-------------------
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if ( state[SDL_SCANCODE_W] ) {
        printf("<W> is pressed.\n");
        moveDir = -90;
        velY = -getHeight() / SPEED;
    }
    if ( state[SDL_SCANCODE_A] ) {
        printf("<A> is pressed.\n");
        moveDir = 180;
        velX = -getWidth() / SPEED;
    }
    if ( state[SDL_SCANCODE_S] ) {
        printf("<S> is pressed.\n");
        moveDir = 90;
        velY = getHeight() / SPEED;
    }
    if ( state[SDL_SCANCODE_D] ) {
        printf("<D> is pressed.\n");
        moveDir = 0;
        velX = getWidth() / SPEED;
    }
       
    mover.setFaceDirection(faceDir);
    mover.setMoveDirection(moveDir);
    mover.setVelX(velX);
    mover.setVelY(velY);
    
    // ------------------
    // Player Firing
    //-------------------
    if ( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) ) {
        fireBullet();
        firing = true;
    }
    else {
        firing = false;
    }

    if ( state[SDL_SCANCODE_E] ) {
        rightArm = "right_arm";
    } else if ( state[SDL_SCANCODE_Q] ) {
        rightArm = "right_arm2";
    }
}

void Player::handle_input( SDL_GameController *controller ) {

    // TODO: need an update() type function
    double faceDir = 0.0;
    double moveDir = 0.0;
    int velX = 0;
    int velY = 0;


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

    // ------------------
    // Player Facing
    //-------------------

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
        faceDir = atan2((double) StickRightY, (double) StickRightX) * (180.0 / M_PI);


        if ( faceDir > -45 && faceDir < 45 ) faceDir = 0;
        else if ( faceDir > -135 && faceDir < -45 ) faceDir = -90;
        else if ( faceDir > 135 || faceDir < -135 ) faceDir = 180;
        else if ( faceDir > 45 && faceDir < 135 ) faceDir = 90;

        //std::cout << "mFaceDirection:  " << mFaceDirection << std::endl;
        //mFaceDirection = 0;
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

    // ------------------
    // Player Firing
    //-------------------
    if ( RightShoulder == 1 ) {
        fireBullet();
        firing = true;
    }
    if ( RightShoulder == 0 ) {

        firing = false;
    }

    if ( AButton == 1 ) {
        rightArm = "right_arm";
    } else if ( BButton == 1 ) {
        rightArm = "right_arm2";
    }

    // ------------------
    // Player Movement
    //-------------------

    if ( ((StickLeftX < -JOYSTICK_DEAD_ZONE) || (StickLeftX > JOYSTICK_DEAD_ZONE)) ||
            ((StickLeftY < -JOYSTICK_DEAD_ZONE) || (StickLeftY > JOYSTICK_DEAD_ZONE)) ) {
        moveDir = atan2((double) StickLeftY, (double) StickLeftX) * (180.0 / M_PI);

        if ( moveDir > -45 && moveDir < 45 ) moveDir = 0;
        else if ( moveDir > -135 && moveDir < -45 ) moveDir = -90;
        else if ( moveDir > 135 || moveDir < -135 ) moveDir = 180;
        else if ( moveDir > 45 && moveDir < 135 ) moveDir = 90;

        //std::cout << "mMoveDirection:  " << mMoveDirection << std::endl;
        //fireBullet();

    }

    // ------------------
    // Player Velocity
    //-------------------

    // If the X axis is neutral
    if ( (StickLeftX > -JOYSTICK_DEAD_ZONE) && (StickLeftX < JOYSTICK_DEAD_ZONE) ) {
        velX = 0;
    }// Adjust the velocity
    else {
        if ( StickLeftX < 0 ) {
            velX = -getWidth() / SPEED;
        } else {
            velX = getWidth() / SPEED;
        }
    }

    // If the Y axis is neutral
    if ( (StickLeftY > -JOYSTICK_DEAD_ZONE) && (StickLeftY < JOYSTICK_DEAD_ZONE) ) {
        velY = 0;
    }// Adjust the velocity
    else {
        if ( StickLeftY < 0 ) {
            velY = -getHeight() / SPEED;
        } else {
            velY = getHeight() / SPEED;
        }
    }

    //std::cout << "xVel: " << xVel << ", yVel: " << yVel << ", direction: " << direction << std::endl;


    mover.setFaceDirection(faceDir);
    mover.setMoveDirection(moveDir);
    mover.setVelX(velX);
    mover.setVelY(velY);

} // handle_input




//          -90
//     -135  |  -45
//         \ | /
//    180 -- + --  0
//         / | \
//     135   |  45
//          90

SDL_Rect Player::getClip( ) {
    SDL_Rect clip;
    int CLIP_SIZE = 30;

    // frame 
    //clip.x = frame*CLIP_SIZE;
    clip.x = (frame / FRAME_COUNT) * getWidth();
    //std::cout << "FRAME= " << frame << std::endl;

    // mMoveDirection
    int y = 0;
    switch ( (int) mover.getFaceDirection() ) {
        case 0: // EAST
            y = CLIP_SIZE * 2;
            break;

        case 90:
            y = 0;
            break;

        case -90:
            y = CLIP_SIZE * 3;
            break;

        case 180: // WEST
            y = CLIP_SIZE;
            break;
    }
    clip.y = y;

    clip.h = CLIP_SIZE;
    clip.w = CLIP_SIZE;

    // mFaceDirection

    return clip;
}

Texture* Player::getTexture( SDL_Renderer* Renderer ) {
    texture = new Texture();

    Texture *headTx = TextureBank::Get(head);
    Texture *torsoTx = TextureBank::Get(torso);
    Texture *leftArmTx = TextureBank::Get(leftArm);
    Texture *rightArmTx = TextureBank::Get(rightArm);
    Texture *legTx = TextureBank::Get(leg);

    SDL_Rect clip = getClip();

    double filp = 0;

    headTx->render(Renderer, getPosX(), getPosY(), &clip, filp);
    torsoTx->render(Renderer, getPosX(), getPosY(), &clip, filp);

    if ( (int) mover.getFaceDirection() == 0 ) { // EAST = RA on top = last  TEAL

        leftArmTx->render(Renderer, getPosX(), getPosY(), &clip, filp);
        rightArmTx->render(Renderer, getPosX(), getPosY(), &clip, filp);
    } else { // WEST (or north/south) = LA on top = last GRAY

        rightArmTx->render(Renderer, getPosX(), getPosY(), &clip, filp);
        leftArmTx->render(Renderer, getPosX(), getPosY(), &clip, filp);
    }

    legTx->render(Renderer, getPosX(), getPosY(), &clip, filp);




    return texture;
}

//std::string Player::getSpriteName() {
//    return mSpriteName;// + std::to_string(frame);
//}

bool Player::move( ) {

    // TODO DIX THIS - THIS IS A HAXK
    int *posX = new int(getPosX());
    int *posY = new int(getPosY());
    mover.move(posX, posY, getBounder());
    setPosX(*posX);
    setPosY(*posY);

    // TODO: better way
    if ( mover.getVelX() != 0 || mover.getVelY() != 0 ) {
        //frame = ++frame % FRAME_COUNT;

        frame += 1;
        if ( frame >= FRAME_COUNT * 3 ) { // must be 3? to be slower
            frame = 0;
        }
    } else {
        frame = 3;
    }
    
    //std::cout << "POS(x,y)=(" << getPosX() << "," << getPosY() << std::endl;

    return false;
}

void Player::fireBullet( ) {
    if ( firing ) return;
    // TODO: better way to get texture size then getting it each time?
    std::string name = "bullet";
    if ( rightArm == "right_arm2" ) {
        name = "laser";
    }

    //Texture *texture = TextureBank::Get(name);
    //if ( texture != nullptr ){
    //auto bullet = std::make_shared<Bullet>(mPosX + PLAYER_WIDTH / 2, mPosY + PLAYER_HEIGHT / 2, mDirection);
    auto bullet = std::make_shared<Bullet>(getPosX(), getPosY(), mover.getFaceDirection(), name, this);
    bullet->setHeight(texture->GetHeight());
    bullet->setWidth(texture->GetWidth());

    mBullets.push_back(bullet);
    //}
}

void Player::updateBullets( ) {

    for ( auto bulletItr = mBullets.begin(); bulletItr != mBullets.end(); ) {
        if ( bulletItr->get()->move() == false ) {
            bulletItr = mBullets.erase(bulletItr);
        } else {
            ++bulletItr;
        }
    }
}