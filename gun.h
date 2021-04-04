#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "config.h"
#include "utils.h"

class Gun {
public:
    Gun(SDL_Renderer* &gRenderer, double x, double y, int _type);
    ~Gun();

    void drawToRender(SDL_Renderer* &gRenderer);

    // show the range shooting circle when click on
    void clickOn();

    // set the range shooting
    void setRange(int r);

    // damage of gun
    void setDamage(int k);
    int getDamage();

    // delay fire
    void setTimeID();
    Uint32 getTimeID();
    int getShotDelayTime();

    double getX();
    double getY();


    // check a enemy in range shooting
    bool onShot(double x, double y);

private:
    // gun
    SDL_Texture* gTexture = NULL;
    SDL_Rect dstrect_g;
    // range shooting circle
    SDL_Texture* cTexture = NULL;
    SDL_Rect dstrect_c;

    // use for delay time the gun fire
    Uint32 timeID;
    int shotDelayTime;

    // position of gun
    double gX, gY;

    // type of gun
    int type;
    // range shooting
    int range;
    // damage
    int damage;
    // price of the gun
    int price;
    // true when click on the gun
    bool showCircle;
};
