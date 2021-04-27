#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "texture.h"
#include "writer.h"

class ctBoard {
public:
    ctBoard();
    ~ctBoard();
    
    void drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double rate);
    void drawNextButton(SDL_Renderer* &gRenderer, gameTexture* &gTexture, int k);

    // draw the gun which is dragged to the map
    void drawTowerChosen(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double x, double y);

    void drawReviewBoard(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double x, double y);

    void pauseMenu();

    void setGem(int k);
    int getGem();
    int getGemOfItemChosen();

    bool clickPauseButton(int x, int y);
    bool clickNextButton(int x, int y);

    bool aTowerIsChosen(int x, int y);
    int getTypeOfGunChosen();

    Uint32 getTimePause();


private:
    void setUpWriterForMoney();
    
    void drawHPBar(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double rate);
    void drawGuns(SDL_Renderer* &gRenderer, gameTexture* &gTexture);
    void drawLocks(SDL_Renderer* &gRenderer, gameTexture* &gTexture, int i);
    // draw current money
    void drawMoney(SDL_Renderer* &gRenderer);

    SDL_Rect dstrect_nb; // next button
    SDL_Rect dstrect_l; // lock
    SDL_Rect dstrect_rvb[6]; // review board

    SDL_Rect dstrect, dstrect_money;

    Writer* writer = NULL;

    int gunItemXPos[6], gunItemYPos[6];
    int gunItemChosen;
    // money
    int gem;

    bool pause_ing;
    Uint32 startPause, timePause;
};