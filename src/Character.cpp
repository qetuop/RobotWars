/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Character.h"
#include "App.h"
#include <iostream>

#include <vector>

static int doOnce = 1;

Character::Character( ) {
    std::cout << "Character created" << std::endl;
    hit = false;
   
}

Character::~Character( ) {
    std::cout << "Character destroyed" << std::endl;
}



