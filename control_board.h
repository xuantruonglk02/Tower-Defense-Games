#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"

class ctBoard {
public:
    ctBoard(SDL_Renderer* &gRenderer);
    ~ctBoard();
    
    void drawToRender(SDL_Renderer* &gRenderer, double rate);
    void drawHPBar(SDL_Renderer* &gRenderer, double rate);
    void drawGuns(SDL_Renderer* &gRenderer);

    bool aGunItemChosen(int x, int y);
    void drawGunChosen(SDL_Renderer* &gRenderer, double x, double y);
    int getTypeOfGunChosen();

private:
    SDL_Texture* cTexture = NULL;
    SDL_Texture* hpbTexture = NULL;
    SDL_Texture* gunTextures[6];

    int gunItemXPos[6], gunItemYPos[6];

    SDL_Rect dstrect;

    int gunItemChosen;
    
};