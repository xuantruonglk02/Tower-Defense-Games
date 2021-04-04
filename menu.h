#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "sound.h"

class Menu {
public:
    Menu(SDL_Renderer* &gRenderer);
    ~Menu();

    void drawMenu(SDL_Renderer* &gRenderer);

    int clickOn(int x, int y);

    void optionsMenu(SDL_Renderer* &gRenderer, Sound* &sound);
    void drawOptionsMenu(SDL_Renderer* &gRenderer);

private:
    SDL_Texture* menuTexture = NULL;
    SDL_Texture* oMenuTexture = NULL;
    SDL_Texture* pButtonTexture = NULL;
    SDL_Texture* oButtonTexture = NULL;
    SDL_Texture* qButtonTexture = NULL;

    SDL_Rect dstrect;
    // up-left position of button
    int pX, pY;
    int oX, oY;
    int qX, qY;
};