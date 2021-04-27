#pragma once

#include <iostream>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "texture.h"

class Supporter {
public:

    Supporter(int x, int y, int _type);
    ~Supporter();

    bool clickOn();

    int checkClickOnUpdateButton(int x, int y, int gem);

    bool inRange(int x, int y);

    int getType();
    int getBuff();

    void setRange(int r);

    void enableUpdate();
    void unenableUpdate();

    void drawToRenderer(SDL_Renderer* &gRenderer, gameTexture* &gTexture);
    void drawRangeCircle(SDL_Renderer* &gRenderer, gameTexture* &gTexture);
    void drawUpdateBoard(SDL_Renderer* &gRenderer, gameTexture* &gTexture);

private:

    SDL_Rect dstrect_bs;

    SDL_Rect dstrect_s;

    SDL_Rect dstrect_r;

    SDL_Point centerPoint;

    Uint32 timeID;

    int max_frame, frame;

    int type; // 0 buff dame, 1 buff range

    int sX, sY;

    double degree;

    int buff;

    int price;

    int range;

    int lever;

    bool showRangeCircle;

};
