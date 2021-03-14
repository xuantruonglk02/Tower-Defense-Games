#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"

class Threat {

public:
    Threat(SDL_Renderer* &gRenderer, double x, double y);
    ~Threat();

    SDL_Texture* getTexture();
    double getX();
    double getY();
    void setX(double x);
    void setY(double y);

    void drawThreat(SDL_Renderer* &gRenderer);
private:
    SDL_Texture* mTexture = NULL;

    double threatX, threatY;

    bool dead = false;
};
