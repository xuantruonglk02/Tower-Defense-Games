#include "bullet.h"
#include "game.h"
Bullet::Bullet(double gX, double gY, Enemy* &_enemy, int _damage, int _type) {
    type = _type;
    damage = _damage;
    success = false;

    firstX = gX; firstY = gY;
    lastX = _enemy->getX(); lastY = _enemy->getY();
    double d = sqrt((lastX - gX)*(lastX - gX) + (lastY - gY)*(lastY - gY));
    
    setDstRect();

    if (type == 0) {
        dstrect.w = BULLET_SIZE; dstrect.h = BULLET_SIZE;

        bulletX = (lastX - gX) * (GUN_H[type][1] / 2 + BULLET_SIZE / 2) / d + gX;
        bulletY = (lastY - gY) * (GUN_H[type][1] / 2 + BULLET_SIZE / 2) / d + gY;

        disToLast = d - GUN_BASE_SIZE/2 - BULLET_SIZE/2;
    } else if (type == 1) {
        dstrect.w = DOUBLE_BULLET_W; dstrect.h = DOUBLE_BULLET_H;

        centerPoint = {DOUBLE_BULLET_W/2, DOUBLE_BULLET_H/2};

        bulletX = (lastX - gX) * (GUN_H[type][1] / 2 + BULLET_SIZE / 2) / d + gX;
        bulletY = (lastY - gY) * (GUN_H[type][1] / 2 + BULLET_SIZE / 2) / d + gY;

        disToLast = d - GUN_BASE_SIZE/2 - BULLET_SIZE/2;
    } else if (type == 2) {
        dstrect.w = 5;

        centerPoint = {2, 0};

        bulletX = (lastX - gX) * (GUN_H[type][1] / 2) / d + gX;
        bulletY = (lastY - gY) * (GUN_H[type][1] / 2) / d + gY;

        disToLast = d - GUN_H[type][1] / 2 - ENEMY_SIZE / 2;
    } else {
        dstrect.h = ROCKET_H[1]; dstrect.w = ROCKET_W[1];

        centerPoint = {ROCKET_W[1] / 2, ROCKET_H[1] / 2};

        bulletX = gX; bulletY = gY;

        disToLast = d - GUN_BASE_SIZE/2 - ROCKET_H[1] + centerPoint.y;

        target = _enemy;

    }
}

Bullet::~Bullet() {}

void Bullet::updateEnemyPosition() {
    if (success) {
        lastX = bulletX - (bulletX - lastX) * (disToLast + 2*BULLET_SPEED[type]) / disToLast;
        lastY = bulletY - (bulletY - lastY) * (disToLast + 2*BULLET_SPEED[type]) / disToLast;
        disToLast += 2*BULLET_SPEED[type];
        return;
    }
    lastX = target->getX(); lastY = target->getY();
    disToLast = sqrt((bulletX - lastX)*(bulletX - lastX) + (bulletY - lastY)*(bulletY - lastY));
}

void Bullet::updateDegree() {
    if (type == 2) {
        double r = sqrt((firstX - lastX)*(firstX - lastX) + (firstY - lastY)*(firstY - lastY));
        degree = asin((lastX - firstX) / r) * 180 / M_PI;
    } else {
        double r = sqrt((bulletX - lastX)*(bulletX - lastX) + (bulletY - lastY)*(bulletY - lastY));
        degree = asin((lastX - bulletX) / r) * 180 / M_PI;
    }
    if (lastY > bulletY) degree = 180 - degree;
}

void Bullet::setDstRect() {
    if (type == 0) {
        dstrect.x = bulletX - BULLET_SIZE/2;
        dstrect.y = bulletY - BULLET_SIZE/2;
    } else if (type == 1) {
        dstrect.x = bulletX - DOUBLE_BULLET_W/2;
        dstrect.y = bulletY - DOUBLE_BULLET_H/2;
    } else if (type == 2) {
        dstrect.x = bulletX - 2;
        dstrect.y = bulletY;
        dstrect.h = disToLast;
    } else {
        dstrect.x = bulletX - ROCKET_W[1] / 2;
        dstrect.y = bulletY - ROCKET_H[1] / 2;
    }
}

void Bullet::updatePos() {
    if (type == 2) {
        bulletX = GUN_H[type][1] / 2 * sin(180 - degree);
        bulletY = GUN_H[type][1] / 2 * cos(180 - degree);
    } else {
        bulletX = (bulletX - lastX) * (disToLast - BULLET_SPEED[type]) / disToLast + lastX;
        bulletY = (bulletY - lastY) * (disToLast - BULLET_SPEED[type]) / disToLast + lastY;
        disToLast -= BULLET_SPEED[type];
    }
}

void Bullet::drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    setDstRect();

    if (type == 0) {
        SDL_RenderCopy(gRenderer, gTexture->bulletTexture[type], NULL, &dstrect);
    } else if (type == 1) {
        updateDegree();
        SDL_RenderCopyEx(gRenderer, gTexture->bulletTexture[type], NULL, &dstrect, degree, &centerPoint, SDL_FLIP_NONE);
    } else if (type == 2) {
        updateDegree();
        SDL_RenderCopyEx(gRenderer, gTexture->bulletTexture[type], NULL, &dstrect, 180 + degree, &centerPoint, SDL_FLIP_NONE);
    } else {
        updateEnemyPosition();
        updateDegree();
        SDL_RenderCopyEx(gRenderer, gTexture->bulletTexture[type], NULL, &dstrect, degree, &centerPoint, SDL_FLIP_NONE);
    }

    updatePos();
}

int Bullet::getType() {return type;}

double Bullet::getX() {return bulletX;}
double Bullet::getY() {return bulletY;}
double Bullet::getLastX() {return lastX;}
double Bullet::getLastY() {return lastY;}

int Bullet::getDamage() {return damage;}

void Bullet::findNewTarget(vector<Enemy*> &enemys) {
    for (int i = 0; i < enemys.size(); i++)
        if (!enemys[i]->isDead()) {
            target = enemys[i];
            return;
        }
}

Enemy* Bullet::getTarget() {return target;}

void Bullet::allTargetKilled() {success = true;}

bool Bullet::outOfScreen() {
    if (bulletX < PLAY_ZONE_X || bulletX > PLAY_ZONE_X + PLAY_ZONE_W || bulletY < PLAY_ZONE_Y || bulletY > PLAY_ZONE_Y + PLAY_ZONE_H)
        return true;
    return false;
}
bool Bullet::hitTheTarget() {
    if (disToLast <= centerPoint.y + ENEMY_SIZE/2) return true;
    else return false;
}
