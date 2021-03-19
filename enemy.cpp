#include "enemy.h"

Enemy::Enemy(SDL_Renderer* &gRenderer, double x, double y, int _type) {
    eTexture = loadTexture(gRenderer, ENEMY_PATH[_type]);
    dstrect.h = ENEMY_SIZE; dstrect.w = ENEMY_SIZE;
    dstrect.x = x - ENEMY_SIZE/2; dstrect.y = y - ENEMY_SIZE/2;
    hp = E_HP[_type];
    type = _type;
}
Enemy::~Enemy() {
    SDL_DestroyTexture(eTexture);
    eTexture = NULL;
}

double Enemy::getX() {return dstrect.x + ENEMY_SIZE/2;}
double Enemy::getY() {return dstrect.y + ENEMY_SIZE/2;}

void Enemy::drawToRender(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, eTexture, NULL, &dstrect);
}

void Enemy::updatePos() {
    dstrect.x += eSpeed;
}

bool Enemy::isSuccess() {
    if (dstrect.x + ENEMY_SIZE/2 >= PLAY_ZONE_X + PLAY_ZONE_W) {
        return true;
    }
    return false;
}