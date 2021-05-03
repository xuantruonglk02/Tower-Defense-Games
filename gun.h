#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "config.h"
#include "utils.h"
#include "texture.h"
#include "sound.h"

class Gun {
public:
    Gun(double x, double y, int _type);
    ~Gun();

    void drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture);
    void drawRangeCircle(SDL_Renderer* &gRenderer, gameTexture* &gTexture);
    void drawUpdateBoard(SDL_Renderer* &gRenderer, gameTexture* &gTexture, int gem);

    void changeShotDirection(int enemyX, int enemyY);

    int getType();

    // show the range shooting circle when click on
    // show update board
    bool clickOn();
    // check click on update button
    int checkClickOnUpdateButton(int x, int y, int gem);

    // set the range shooting
    void setRange(int r);

    // damage of gun
    void setDamage(int k);
    int getDamage();

    void setBuff(int typeOfSupporter, int buff);

    // delay fire
    void setTimeID();
    Uint32 getTimeID();
    int getShotDelayTime();

    void unenableUpdate();

    int getX();
    int getY();

    void fire(Sound* sound);

    // check a enemy in range shooting
    bool onShot(double x, double y);

private:
    // border = 5
    // word h = 15
    // chu lui 3
    // lever lui 5
    // cong cach phai 4
    // 68

    // gun
    SDL_Rect dstrect_g[2];
    // gun base
    SDL_Rect dstrect_bs;
    // rocket not fire
    SDL_Rect dstrest_rk;
    // range shooting circle
    SDL_Rect dstrect_c;
    // update board
    SDL_Rect dstrect_ub;
    // inc button
    SDL_Rect dstrect_ib[3];
    // lever
    SDL_Rect dstrect_l[3];
    // block
    SDL_Rect dstrect_b[3];

    SDL_Point centerPoint_g[2];
    SDL_Point centerPoint_rk;

    double degree;

    // position of gun
    int gX, gY;

    // type of gun
    int type;

    // damage
    int damage, d_lever;
    // speed
    Uint32 timeID;
    int shotDelayTime, s_lever;
    // range shooting
    int range, r_lever;

    // price of the gun
    int price;

    int frame;

    bool showRocket;

    // true when click on the gun
    bool showUpdate;
    bool showUpdateButton[3]; // dame speed range
};
