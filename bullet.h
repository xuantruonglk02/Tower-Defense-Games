#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"

class Bullet {
public:
    Bullet(SDL_Renderer* &gRenderer, double fX, double fY, double bX, double bY, double d, int _damage);
    ~Bullet();

    // set position
    void setFirstX(double x);
    void setFirstY(double y);
    void setX(double x);
    void setY(double y);
    // distance from first position to current position
    void setDistance(double d);
    // update position
    void updatePos(int k);

    void drawToRender(SDL_Renderer* &gRenderer);

    double getFirstX();
    double getFirstY();
    double getX();
    double getY();
    double getDistance();

    int getDamage();

    bool outOfScreen();

private:

    SDL_Texture* bTexture = NULL;

    double firstX, firstY;
    double bulletX, bulletY;
    double dis;

    int damage;

};