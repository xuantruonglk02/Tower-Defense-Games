#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "enemy.h"

class Bullet {
public:
    Bullet(SDL_Renderer* &gRenderer, double gX, double gY, Enemy* &_enemy, int _damage, int _type);
    ~Bullet();

    void updateEnemyPosition();
    void updateDegree();
    void updatePos(int k);
    void setDstRect();

    void drawToRender(SDL_Renderer* &gRenderer);

    int getType();

    double getX();
    double getY();
    double getLastX();
    double getLastY();

    int getDamage();

    void setTarget(Enemy* enemy);
    Enemy* getTarget();

    void targetKilled();

    bool outOfScreen();
    bool hitTheTarget();

private:

    SDL_Texture* bTexture = NULL;

    SDL_Point centerPoint;

    SDL_Rect dstrect;

    Enemy* target = NULL;

    double firstX, firstY;
    double lastX, lastY;
    double bulletX, bulletY;
    double disToLast;

    int type;
    int damage;
    double degree;
    bool success;
};