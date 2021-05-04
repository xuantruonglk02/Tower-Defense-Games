#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "sound.h"
#include "texture.h"

class Menu {
public:
    Menu();
    ~Menu();

    void setDstRectButton(bool resume);

    void drawMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture);

    int clickOn(int x, int y);

    void optionsMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture, Sound* &sound);
    void drawOptionsMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture, Sound* &sound);

    void selectMapMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture, Sound* &sound, int &indexOfMap);

private:
    // button
    SDL_Rect dstrect_p, dstrect_r, dstrect_sm, dstrect_o, dstrect_q;
    // options menu
    SDL_Rect dstrect_om;
    // select map menu
    SDL_Rect dstrect_smm;
    // mute icon
    SDL_Rect dstrect_m_m, dstrect_m_s;

};