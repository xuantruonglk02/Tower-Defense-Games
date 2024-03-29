#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "texture.h"
#include "map.h"

using std::vector;

class Enemy {
public:
    // creat enemy with first x = 0 and first y = y
    Enemy(int y, int _type);
    ~Enemy();

    // use map of road from map to move
    void updatePos(const vector<int> &dir, const vector<int> &xRoad, const vector<int> &yRoad);

    void drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture);

    int getX();
    int getY();
    // gei position on road for sort
    int getCurrentPos();

    // get damage to base
    int getDamage();

    // get the money when kill the enemy
    int getPrize();

    // check enemy is shotted
    bool getHit(double bX, double bY, int bDamage, int bType);
    // check enemy get hit by roket boom
    void getBoom(double bX, double bY, int bDamage);

    void updateHPBar();

    // check enemy go to the base
    bool isSuccess();
    // check hp enemy less than 0
    bool isDead();


private:

    SDL_Rect dstrect_e;
    SDL_Rect dstrect_hp;

    Uint32 effectTimeID;

    // type of enemy
    int type;
    
    // current position of enemy on road
    int curPos;

    double speed;
    double eX, eY;

    int damage;
    int hp;
    // the money player can get after kill the enemy
    int prize;

    bool showHP;
};