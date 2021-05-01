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
#include "sound.h"

class ctBoard {
public:
    ctBoard();
    ~ctBoard();
    
    bool aTowerIsChosen(int x, int y);
    int getTypeOfGunChosen();
    void drawTowerChosen(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double x, double y);

    void drawReviewBoard(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double x, double y);

    void setGem(int k);
    int getGem();
    int getGemOfItemChosen();

    Uint32 getTimePause();
    bool clickPauseButton(int x, int y);
    void pauseMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture, Sound* &sound, bool &resume);

    bool clickNextButton(int x, int y);
    void drawNextButton(SDL_Renderer* &gRenderer, gameTexture* &gTexture, int k);

    void drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double rate);

private:
    void setUpWriterForMoney();
    
    void drawHPBar(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double rate);
    void drawGuns(SDL_Renderer* &gRenderer, gameTexture* &gTexture);
    void drawLocks(SDL_Renderer* &gRenderer, gameTexture* &gTexture, int i);
    void drawMoney(SDL_Renderer* &gRenderer);

    SDL_Rect dstrect_nb; // next button
    SDL_Rect dstrect_pm; // pause menu
    SDL_Rect dstrect_l; // lock
    SDL_Rect dstrect_rvb[6]; // review board
    SDL_Rect dstrect_hp; // hp bar
    SDL_Rect dstrect_pb; //pause button
    SDL_Rect dstrect_m_m, dstrect_m_s; // mute
    SDL_Rect dstrect_money;

    Writer* writer = NULL;

    int gunItemXPos[6], gunItemYPos[6];
    int gunItemChosen;
    // money
    int gem;

    Uint32 startPause;
};