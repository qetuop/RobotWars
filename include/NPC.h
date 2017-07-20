/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPC.h
 * Author: brian
 *
 * Created on January 1, 2016, 5:54 PM
 */
#include <SDL2/SDL.h>

#include <memory>
#include <list>

#include "Character.h"
#include "Bullet.h"

#ifndef NPC_H
#define NPC_H

#ifdef __cplusplus
extern "C" {
#endif

    class NPC : public Character {
    public:

        // current animation frame to draw
        int frame;
        
    public:
        NPC();
        ~NPC();
        
        void hit();
        
        virtual std::string getSpriteName();
    };



#ifdef __cplusplus
}
#endif

#endif /* NPC_H */

