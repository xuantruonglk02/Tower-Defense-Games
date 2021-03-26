#include "enemy.h"

Enemy::Enemy(SDL_Renderer* &gRenderer, int y, int _type) {
    eTexture = loadTexture(gRenderer, ENEMY_PATH[_type]);
    dstrect.h = ENEMY_SIZE; dstrect.w = ENEMY_SIZE;
    dstrect.x = -ENEMY_SIZE/2; dstrect.y = y - ENEMY_SIZE/2;
    hp = E_HP[_type];
    speed = E_SPEED[_type];
    damage = E_DAMAGE[_type];
    type = _type;
}
Enemy::~Enemy() {
    SDL_DestroyTexture(eTexture);
    eTexture = NULL;
}

int Enemy::getX() {return dstrect.x + ENEMY_SIZE/2;}
int Enemy::getY() {return dstrect.y + ENEMY_SIZE/2;}
int Enemy::getDam() {return damage;}

void Enemy::drawToRender(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, eTexture, NULL, &dstrect);
}

void Enemy::updatePos() {
    dstrect.x += speed;
}

bool Enemy::isSuccess() {
    if (dstrect.x >= PLAY_ZONE_X + PLAY_ZONE_W) {
        return true;
    }
    return false;
}

bool Enemy::getHit(double bX, double bY, int damamge) {
    if (sqrt((dstrect.x + ENEMY_SIZE/2 - bX)*(dstrect.x + ENEMY_SIZE/2 - bX) + (dstrect.y + ENEMY_SIZE/2 - bY)*(dstrect.y + ENEMY_SIZE/2 - bY)) <= ENEMY_SIZE/2 + BULLET_SIZE/2) {
        hp -= damamge;
        return true;
    }
    return false;
}

bool Enemy::isDead() {
    if (hp <= 0) return true;
    else return false;
}