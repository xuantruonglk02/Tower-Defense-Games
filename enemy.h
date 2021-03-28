#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "map.h"

class Enemy {
public:
    Enemy(SDL_Renderer* &gRenderer, int y, int _type);
    ~Enemy();

    int getX();
    int getY();
    int getDam();

    void drawToRender(SDL_Renderer* &gRenderer);

    void updatePos(const vector<int> &dir, const vector<int> &xRoad, const vector<int> &yRoad);

    bool isSuccess();
    
    bool getHit(double bX, double bY, int damamge);
    bool isDead();

private:
    SDL_Texture* eTexture;
    SDL_Rect dstrect;
    int type;
    int speed;
    int damage;
    int hp;
    int curPos;
};