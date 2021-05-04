#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "texture.h"
#include "enemy.h"

class Bullet {
public:
    Bullet(double gX, double gY, Enemy* &_enemy, int _damage, int _type);
    ~Bullet();

    void updateEnemyPosition();
    void updateDegree();
    void updatePos();
    void setDstRect();

    void drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture);

    int getType();

    double getX();
    double getY();
    double getLastX();
    double getLastY();

    int getDamage();

    void findNewTarget(vector<Enemy*> &enemys);
    Enemy* getTarget();

    void allTargetKilled();

    bool outOfScreen();
    bool hitTheTarget();

private:

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