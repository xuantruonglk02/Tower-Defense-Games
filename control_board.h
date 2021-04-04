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
    // draw the gun which is dragged to the map
    void drawGunChosen(SDL_Renderer* &gRenderer, double x, double y);

    void setGem(int k);
    int getGem();

    bool clickPauseButton(int x, int y);
    bool aGunItemIsChosen(int x, int y);
    int getTypeOfGunChosen();


private:
    // control board texture
    SDL_Texture* cTexture = NULL;
    // pause button texture
    SDL_Texture* pTexture = NULL;
    // lock texture
    SDL_Texture* lTexture = NULL;
    // hp bar texture
    SDL_Texture* hpbTexture = NULL;
    // 6 gun textures
    SDL_Texture* gunTextures[6];

    SDL_Rect dstrect;

    int gunItemXPos[6], gunItemYPos[6];
    int gunItemChosen;
    // money
    int gem;
};