#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"

class Menu {
public:
    Menu(SDL_Renderer* &gRenderer);
    ~Menu();

    void drawMenu(SDL_Renderer* &gRenderer);

    int clickOn(int x, int y);

    void option();

private:
    SDL_Texture* welcome = NULL;
    SDL_Texture* pButton = NULL;
    SDL_Texture* oButton = NULL;
    SDL_Texture* qButton = NULL;

    int pX, pY;
    int oX, oY;
    int qX, qY;
};