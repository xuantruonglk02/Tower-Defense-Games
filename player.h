#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"

class Player {

public:
    Player(SDL_Renderer* &gRenderer);
    ~Player();

    SDL_Texture* getTexture();
    double getX();
    double getY();
    void setX(double x);
    void setY(double y);

    void drawPlayer(SDL_Renderer* &gRenderer);
    
private:

    SDL_Texture* mTexture = NULL;
    
    double playerX, playerY;

};
