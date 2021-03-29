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
    void drawLocks(SDL_Renderer* &gRenderer, int i);

    void setGem(int k);
    int getGem();

    void clickEvent(int x, int y);
    bool aGunItemChosen(int x, int y);
    int getTypeOfGunChosen();

    void drawGunChosen(SDL_Renderer* &gRenderer, double x, double y);
    void pause();

private:
    SDL_Texture* cTexture = NULL;
    SDL_Texture* pTexture = NULL;
    SDL_Texture* lTexture = NULL;
    SDL_Texture* hpbTexture = NULL;
    SDL_Texture* gunTextures[6];

    SDL_Rect dstrect;

    int gunItemXPos[6], gunItemYPos[6];

    int gunItemChosen;
    int gem;
};