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
    // creat enemy with first x = 0 and first y = y
    Enemy(SDL_Renderer* &gRenderer, int y, int _type);
    ~Enemy();

    // use map of road from map to move
    void updatePos(const vector<int> &dir, const vector<int> &xRoad, const vector<int> &yRoad);

    void drawToRender(SDL_Renderer* &gRenderer);

    int getX();
    int getY();

    // get damage to base
    int getDam();

    // get the money when kill the enemy
    int getPrize();

    // check enemy is shotted
    bool getHit(double bX, double bY, int damamge);

    // check enemy go to the base
    bool isSuccess();
    // check hp enemy less than 0
    bool isDead();

private:
    // enemy texture
    SDL_Texture* eTexture;
    SDL_Rect dstrect;

    // type of enemy
    int type;
    
    // current position of enemy on road
    int curPos;

    int speed;
    int damage;
    int hp;
    // the money player can get after kill the enemy
    int prize;
};