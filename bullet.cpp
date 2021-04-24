#include "bullet.h"

Bullet::Bullet(SDL_Renderer* &gRenderer, double gX, double gY, Enemy* &_enemy, int _damage, int _type) {
    type = _type;
    damage = _damage;
    success = false;

    firstX = gX; firstY = gY;
    lastX = _enemy->getX(); lastY = _enemy->getY();
    double d = sqrt((lastX - gX)*(lastX - gX) + (lastY - gY)*(lastY - gY));

    if (type < 2) {
        bTexture = loadTexture(gRenderer, BULLET_PATH[0]);
        setDstRect();

        bulletX = (lastX - gX) * (GUN_H[type][1] / 2 + BULLET_SIZE / 2) / d + gX;
        bulletY = (lastY - gY) * (GUN_H[type][1] / 2 + BULLET_SIZE / 2) / d + gY;

        disToLast = d - GUN_BASE_SIZE/2 - BULLET_SIZE/2;
    } else if (type == 2) {
        bTexture = loadTexture(gRenderer, BULLET_PATH[1]);
        setDstRect();

        centerPoint = {1, 0};

        firstX = (lastX - gX) * (GUN_H[type][1] / 2) / d + gX;
        firstY = (lastY - gY) * (GUN_H[type][1] / 2) / d + gY;

        disToLast = d - GUN_H[type][1] / 2 - ENEMY_SIZE / 2;

    } else {
        bTexture = loadTexture(gRenderer, BULLET_PATH[2]);
        setDstRect();

        centerPoint = {ROCKET_W[1] / 2, ROCKET_H[1] / 2};

        bulletX = gX; bulletY = gY;

        disToLast = d - GUN_BASE_SIZE/2 - ROCKET_H[1] + centerPoint.y;

        target = _enemy;

    }
}

Bullet::~Bullet() {
    SDL_DestroyTexture(bTexture);
    bTexture = NULL;
}

void Bullet::updateEnemyPosition() {
    if (success) {
        lastX = bulletX - (bulletX - lastX) * (disToLast + 20) / disToLast;
        lastY = bulletY - (bulletY - lastY) * (disToLast + 20) / disToLast;
        disToLast += 20;
        return;
    }
    lastX = target->getX(); lastY = target->getY();
    disToLast = sqrt((bulletX - lastX)*(bulletX - lastX) + (bulletY - lastY)*(bulletY - lastY));
}

void Bullet::updateDegree() {
    double r = sqrt((bulletX - lastX)*(bulletX - lastX) + (bulletY - lastY)*(bulletY - lastY));
    degree = asin((lastX - bulletX) / r) * 180 / M_PI;
    if (lastY > bulletY) degree = 180 - degree;
}

void Bullet::updatePos(int k) {
    bulletX = (bulletX - lastX) * (disToLast - BULLET_SPEED[type]) / disToLast + lastX;
    bulletY = (bulletY - lastY) * (disToLast - BULLET_SPEED[type]) / disToLast + lastY;
    disToLast -= BULLET_SPEED[type];
}

void Bullet::setDstRect() {
    if (type < 2) {
        dstrect.x = bulletX - BULLET_SIZE/2;
        dstrect.y = bulletY - BULLET_SIZE/2;
        dstrect.h = BULLET_SIZE; dstrect.w = BULLET_SIZE;
    } else if (type == 2) {
        dstrect.x = firstX - 1;
        dstrect.y = firstY;
        dstrect.h = disToLast; dstrect.w = 3;
    } else {
        dstrect.x = bulletX - ROCKET_W[1] / 2;
        dstrect.y = bulletY - ROCKET_H[1] / 2;
        dstrect.h = ROCKET_H[1]; dstrect.w = ROCKET_W[1];
    }
}

void Bullet::drawToRender(SDL_Renderer* &gRenderer) {
    if (type < 2) {
        setDstRect();
        SDL_RenderCopy(gRenderer, bTexture, NULL, &dstrect);
    } else if (type == 2) {
        //SDL_RenderDrawLine(gRenderer, firstX, firstY, lastX, lastY);
        updateDegree();
        SDL_RenderCopyEx(gRenderer, bTexture, NULL, &dstrect, degree, &centerPoint, SDL_FLIP_NONE);
    } else {
        updateEnemyPosition();
        updateDegree();
        setDstRect();
        SDL_RenderCopyEx(gRenderer, bTexture, NULL, &dstrect, degree, &centerPoint, SDL_FLIP_NONE);
    }

    if (type != 2) updatePos(type);
}

int Bullet::getType() {return type;}

double Bullet::getX() {return bulletX;}
double Bullet::getY() {return bulletY;}
double Bullet::getLastX() {return lastX;}
double Bullet::getLastY() {return lastY;}

int Bullet::getDamage() {return damage;}

void Bullet::setTarget(Enemy* enemy) {target = enemy;}
Enemy* Bullet::getTarget() {return target;}

void Bullet::targetKilled() {success = true;}

bool Bullet::outOfScreen() {
    if (bulletX - BULLET_SIZE/2 < PLAY_ZONE_X || bulletX + BULLET_SIZE/2 > PLAY_ZONE_X + PLAY_ZONE_W
        || bulletY - BULLET_SIZE/2 < PLAY_ZONE_Y || bulletY + BULLET_SIZE/2 > PLAY_ZONE_Y + PLAY_ZONE_H)
        return true;
    return false;
}
bool Bullet::hitTheTarget() {
    if (disToLast <= centerPoint.y + ENEMY_SIZE/2) return true;
    else return false;
}
