/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bullet.h
 * Author: brian
 *
 * Created on January 2, 2016, 7:33 PM
 */

#include "MoveableObject.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet : public MoveableObject {
public:
  
public:
    Bullet();
    Bullet(int _x, int _y, double _direction, std::string name);
    ~Bullet();

    bool move();
    
    void render(SDL_Renderer* Renderer);
    
};

#endif /* BULLET_H */

