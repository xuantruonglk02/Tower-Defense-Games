#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"

class Gun {
public:
    Gun(SDL_Renderer* &gRenderer, double x, double y, int _type);
    ~Gun();

    double getX();
    double getY();

    void drawToRender(SDL_Renderer* &gRenderer);

    void setDamage(int k);
    int getDamage();

    void clickEvent(int x, int y);

    bool onShot(double x, double y);

private:
    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;
    double gX, gY;
    int type;
    double range;
    int damage;
    int price;
};