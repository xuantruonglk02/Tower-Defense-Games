#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "writer.h"

class ctBoard {
public:
    ctBoard(SDL_Renderer* &gRenderer);
    ~ctBoard();
    
    void drawToRender(SDL_Renderer* &gRenderer, double rate);
    // draw the gun which is dragged to the map
    void drawGunChosen(SDL_Renderer* &gRenderer, double x, double y);

    void pauseMenu();

    void setGem(int k);
    int getGem();
    int getGemOfItemChosen();

    bool clickPauseButton(int x, int y);
    bool aGunItemIsChosen(int x, int y);
    int getTypeOfGunChosen();

    Uint32 getTimePause();


private:
    void setUpWriterForMoney();
    
    void drawHPBar(SDL_Renderer* &gRenderer, double rate);
    void drawGuns(SDL_Renderer* &gRenderer);
    void drawLocks(SDL_Renderer* &gRenderer, int i);
    // draw current money
    void drawMoney(SDL_Renderer* &gRenderer);


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
    // range circle texture
    SDL_Texture* rTexture = NULL;
    // money
    SDL_Texture* mTexture = NULL;
    // review board
    SDL_Texture* rvTexture = NULL;

    SDL_Rect dstrect, dstrect_money;

    Writer* writer = NULL;

    int gunItemXPos[6], gunItemYPos[6];
    int gunItemChosen;
    // money
    int gem;

    bool pause_ing;
    Uint32 startPause, timePause;
};