/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.h
 * Author: brian
 *
 * Created on January 1, 2016, 5:54 PM
 */
#include <SDL2/SDL.h>

#include <memory>
#include <list>

#include "MoveableObject.h"

#ifndef CHARACTER_H
#define CHARACTER_H

#ifdef __cplusplus
extern "C" {
#endif

    class Character : public MoveableObject {
    public:       
        bool hit;

    public:
        Character();
        ~Character();
    };

#ifdef __cplusplus
}
#endif

#endif /* CHARACTER_H */

