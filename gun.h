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
    // show update board
    bool clickOn();
    // check click on update button
    int checkClickOnUpdateButton(int x, int y, int gem);

    // set the range shooting
    void setRange(int r);

    // damage of gun
    void setDamage(int k);
    int getDamage();

    // delay fire
    void setTimeID();
    Uint32 getTimeID();
    int getShotDelayTime();

    //
    void unShowUpdate();

    double getX();
    double getY();


    // check a enemy in range shooting
    bool onShot(double x, double y);

private:
    const int UPDATE_BOARD_HEIGHT = 214;
    const int UPDATE_BOARD_WIDTH = 124;
    const int UPDATE_BOARD_BORDER = 5;
    
    const int INC_BUTTON_SIZE = 30;
    // border = 5
    // word h = 15
    // chu lui 3
    // lever lui 5
    // cong cach phai 4
    // 68

    // gun
    SDL_Texture* gTexture = NULL;
    SDL_Rect dstrect_g;
    // range shooting circle
    SDL_Texture* cTexture = NULL;
    SDL_Rect dstrect_c;
    // update board
    SDL_Texture* ubTexture = NULL;
    SDL_Rect dstrect_ub;
    // inc button
    SDL_Texture* ibTexture = NULL;
    SDL_Rect dstrect_ib[3];
    // lever
    SDL_Texture* lTexture = NULL;
    SDL_Rect dstrect_l[3];
    // block
    SDL_Texture* bTexture = NULL;
    SDL_Rect dstrect_b[3];

    // position of gun
    double gX, gY;

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
    // true when click on the gun
    bool showUpdate;
};
