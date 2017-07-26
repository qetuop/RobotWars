/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: brian
 *
 * Created on January 1, 2016, 5:54 PM
 */
#include <SDL2/SDL.h>

#include <memory>
#include <list>

#include "Bullet.h"
#include "Character.h"

#include "Texture.h"

#ifndef PLAYER_H
#define PLAYER_H

#ifdef __cplusplus
extern "C" {
#endif

    class Player : public Character {
    public:

        //bool firing;
        std::list<std::shared_ptr<Bullet>> mBullets;
        
        // current animation frame to draw
        int frame; // FRAME_COUNT = 3; = 0 1 2 0 1 2
        
        //int direction; // N = 3, E = 2, S = 0, W = 1
        
        Texture *texture;
        std::string head;
        std::string torso;
        std::string leftArm;
        std::string rightArm;
        std::string leg;
        
        bool firing;

    public:
        Player();
        ~Player();
             
        
        void handle_input(SDL_GameController *controller);

        SDL_Rect getClip();
        Texture* getTexture(SDL_Renderer* Renderer);
        
        virtual bool move();
        
        virtual std::string getSpriteName();
        
        void fireBullet();
        void updateBullets();
        
    };



#ifdef __cplusplus
}
#endif

#endif /* PLAYER_H */

