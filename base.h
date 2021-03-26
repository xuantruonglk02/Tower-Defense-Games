#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "utils.h"

class Base {
public:
    Base(SDL_Renderer* &gRenderer, int y);
    ~Base();

    void drawToRender(SDL_Renderer* &gRenderer);

    void setHP(int eHP);
    double getHPRate();

    bool lose();

private:
    const int MAXHP = 500;

    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;
    int hp;
};
