#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"

class Base {
public:
    Base(SDL_Renderer* &gRenderer, int y);
    ~Base();

    void setHP(int eHP);

    void drawToRender(SDL_Renderer* &gRenderer);
    
    double getHPRate();

    // check when hp is less than 0
    bool destroyed();

private:
    const int MAXHP = 500;

    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;
    int hp;
};
