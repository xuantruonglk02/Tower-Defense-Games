#include "enemy.h"

Enemy::Enemy(int y, int _type) {
    dstrect_e.h = ENEMY_SIZE; dstrect_e.w = ENEMY_SIZE;

    dstrect_hp.w = dstrect_e.w; dstrect_hp.h = 5;

    eX = 0; eY = y;

    // use the first value array
    type = _type;
    hp = E_HP[_type];
    speed = E_SPEED[_type];
    damage = E_DAMAGE[_type];
    prize = E_PRIZE[_type];

    // first position on road
    curPos = 0;

    showHP = false;
}
Enemy::~Enemy() {
}

void Enemy::updatePos(const vector<int> &dir, const vector<int> &xRoad, const vector<int> &yRoad) {
    if (SDL_GetTicks() - effectTimeID >= 3000) speed = E_SPEED[type];

    if (curPos == xRoad.size()) {eX += speed; return;}
    switch (dir[curPos]) {
        case 0:
            eY -= speed;
            if (abs(eY - yRoad[curPos]*50-25 - PLAY_ZONE_Y) <= speed) {eY = yRoad[curPos]*50+25 + PLAY_ZONE_Y; curPos++;}
            break;
        case 1:
            eX += speed;
            if (abs(eX - xRoad[curPos]*50-25 - PLAY_ZONE_X) <= speed) {eX = xRoad[curPos]*50+25 + PLAY_ZONE_X; curPos++;}
            break;
        case 2:
            eY += speed;
            if (abs(eY - yRoad[curPos]*50-25 - PLAY_ZONE_Y) <= speed) {eY = yRoad[curPos]*50+25 + PLAY_ZONE_Y; curPos++;}
            break;
        case 3:
            eX -= speed;
            if (abs(eX - xRoad[curPos]*50-25 - PLAY_ZONE_X) <= speed) {eX = xRoad[curPos]*50+25 + PLAY_ZONE_X; curPos++;}
            break;
    }
}

void Enemy::drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    dstrect_e.x = eX - ENEMY_SIZE/2;
    dstrect_e.y = eY - ENEMY_SIZE/2;
    SDL_RenderCopy(gRenderer, gTexture->enemyTexture[type], NULL, &dstrect_e);

    if (showHP) {
        dstrect_hp.x = dstrect_e.x;
        dstrect_hp.y = dstrect_e.y - dstrect_hp.h - 3;
        SDL_RenderCopy(gRenderer, gTexture->hpBarTexture, NULL, &dstrect_hp);
        
        if (SDL_GetTicks() - effectTimeID > 3000) showHP = false;
    }

}

int Enemy::getX() {return eX;}
int Enemy::getY() {return eY;}
int Enemy::getCurrentPos() {return curPos;}
int Enemy::getDamage() {return damage;}
int Enemy::getPrize() {return prize;}

bool Enemy::getHit(double bX, double bY, int bDamage, int bType) {
    int range;
    if (bType < 2) range = ENEMY_SIZE/2 + BULLET_SIZE/2;
    else if (bType == 2) range = ENEMY_SIZE/2;
    else range = ENEMY_SIZE/2 + ROCKET_H[1]/2;

    if (sqrt((eX - bX)*(eX - bX) + (eY - bY)*(eY - bY)) > range)
        return false;

    if (bType == 2) {
        effectTimeID = SDL_GetTicks();
        speed = E_SPEED[type] / 2;
    }

    hp -= bDamage;
    updateHPBar();

    effectTimeID = SDL_GetTicks();
    showHP = true;

    return true;
}

void Enemy::getBoom(double bX, double bY, int bDamage) {
    if (sqrt((eX - bX)*(eX - bX) + (eY - bY)*(eY - bY)) <= BOOM_RANGE) {
        hp -= bDamage / 2;
        updateHPBar();

        effectTimeID = SDL_GetTicks();
        showHP = true;
    }
}

void Enemy::updateHPBar() {
    double r = hp * 1.0 / E_HP[type];
    dstrect_hp.w = (int)(dstrect_e.w * r);
    dstrect_hp.x = dstrect_e.x + (dstrect_e.w - dstrect_hp.w) / 2;
}

bool Enemy::isSuccess() {
    if (dstrect_e.x >= PLAY_ZONE_X + PLAY_ZONE_W) {
        return true;
    }
    return false;
}

bool Enemy::isDead() {
    if (hp <= 0) return true;
    else return false;
}
