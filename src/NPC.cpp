/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "NPC.h"
#include "App.h"

#include <iostream>


static int doOnce = 1;

NPC::NPC( ) {
    std::cout << "NPC created" << std::endl;
    
    // TODO: make a setX/Y func
    mPosX = 0;
    mPosY = 0;
    
    mBounder.x = mPosX;
    mBounder.y = mPosY;
    
    mSpriteName = "attacker_";   
    
    frame = 0;

}

NPC::~NPC( ) {
    std::cout << "NPC destroyed" << std::endl;
}

std::string NPC::getSpriteName() {
    return mSpriteName + std::to_string(frame);
}

void NPC::hit() {
    frame = 1;
}