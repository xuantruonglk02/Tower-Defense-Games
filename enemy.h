#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"

class Enemy {
public:
    Enemy(SDL_Renderer* &gRenderer, double x, double y, int _type);
    ~Enemy();

    double getX();
    double getY();

    void drawToRender(SDL_Renderer* &gRenderer);

    void updatePos();

    bool isSuccess();
    
    bool getHit(double bX, double bY, int damamge);
    bool isDead();

private:
    SDL_Texture* eTexture;
    SDL_Rect dstrect;
    int type;
    int eSpeed = 1;
    int hp;
};