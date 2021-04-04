#include "bullet.h"

Bullet::Bullet(SDL_Renderer* &gRenderer, double fX, double fY, double bX, double bY, double d, int _damage) {
    bTexture = loadTexture(gRenderer, BULLET_PATH);
    firstX = fX; firstY = fY;
    bulletX = bX; bulletY = bY;
    dis = d;
    damage = _damage;
}

Bullet::~Bullet() {
    SDL_DestroyTexture(bTexture);
    bTexture = NULL;
}

void Bullet::setFirstX(double x) {firstX = x;}
void Bullet::setFirstY(double y) {firstY = y;}
void Bullet::setX(double x) {bulletX = x;}
void Bullet::setY(double y) {bulletY = y;}
void Bullet::setDistance(double d) {dis = d;}

void Bullet::updatePos(int k) {
    bulletX = (bulletX - firstX) * (dis + BULLET_SPEED[k]) / dis + firstX;
    bulletY = (bulletY - firstY) * (dis + BULLET_SPEED[k]) / dis + firstY;
    dis = dis + BULLET_SPEED[k];
}

void Bullet::drawToRender(SDL_Renderer* &gRenderer) {
    SDL_Rect dstrect;
    dstrect.x = bulletX - BULLET_SIZE/2;
    dstrect.y = bulletY - BULLET_SIZE/2;
    dstrect.h = BULLET_SIZE; dstrect.w = BULLET_SIZE;
    SDL_RenderCopy(gRenderer, bTexture, NULL, &dstrect);
}

double Bullet::getFirstX() {return firstX;}
double Bullet::getFirstY() {return firstY;}
double Bullet::getX() {return bulletX;}
double Bullet::getY() {return bulletY;}
double Bullet::getDistance() {return dis;}

int Bullet::getDamage() {return damage;}

bool Bullet::outOfScreen() {
    if (bulletX - BULLET_SIZE/2 < PLAY_ZONE_X || bulletX + BULLET_SIZE/2 > PLAY_ZONE_X + PLAY_ZONE_W
        || bulletY - BULLET_SIZE/2 < PLAY_ZONE_Y || bulletY + BULLET_SIZE/2 > PLAY_ZONE_Y + PLAY_ZONE_H)
        return true;
    return false;
}