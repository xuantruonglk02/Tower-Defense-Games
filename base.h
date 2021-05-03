#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "texture.h"

class Base {
public:
    Base(int y);
    ~Base();

    void setHP(int eHP);
    void drawGettingHitEffect(SDL_Renderer* &gRenderer, gameTexture* &gTexture);
    
    void drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture);
    
    double getHPRate();

    // check when hp is less than 0
    bool destroyed();

private:
    const int MAXHP = 500;

    SDL_Rect dstrect;
    int hp;
};
