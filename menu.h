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

    void drawMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture);

    int clickOn(int x, int y);

    void optionsMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture, Sound* &sound);
    void drawOptionsMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture);

private:

    SDL_Rect dstrect;
    // options menu
    SDL_Rect dstrect_om;
    // button
    SDL_Rect dstrect_p, dstrect_o, dstrect_q;
    // resume button
    SDL_Rect dstrect_r;
    // mute icon
    SDL_Rect dstrect_m_m, dstrect_m_s;

    bool musicPlaying, soundPlaying;
};