#pragma once

#include <iostream>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"

class Supporter {
public:

    Supporter(SDL_Renderer* &gRenderer, int x, int y, int _type);
    ~Supporter();

    bool clickOn();

    int checkClickOnUpdateButton(int x, int y, int gem);

    bool inRange(int x, int y);

    int getType();
    int getBuff();

    void setRange(int r);

    void enableUpdate();
    void unenableUpdate();

    void drawToRenderer(SDL_Renderer* &gRenderer);
    void drawRangeCircle(SDL_Renderer* &gRenderer);
    void drawUpdateBoard(SDL_Renderer* &gRenderer);

private:

    // supporter
    SDL_Texture* sTexture = NULL;
    SDL_Rect dstrect_s;

    // range circle
    SDL_Texture* rTexture = NULL;
    SDL_Rect dstrect_r;

    int type; // 0 buff dame, 1 buff range

    int sX, sY;

    int buff;

    int price;

    int range;

    int lever;

    bool showUpdate;

};
