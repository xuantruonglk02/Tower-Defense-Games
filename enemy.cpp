#include "enemy.h"

Enemy::Enemy(SDL_Renderer* &gRenderer, int y, int _type) {
    // load enemy texture
    eTexture = loadTexture(gRenderer, ENEMY_PATH[_type]);
    // 
    dstrect.h = ENEMY_SIZE; dstrect.w = ENEMY_SIZE;
    dstrect.x = -ENEMY_SIZE/2; dstrect.y = y - ENEMY_SIZE/2;

    // use the first value array
    type = _type;
    hp = E_HP[_type];
    speed = E_SPEED[_type];
    damage = E_DAMAGE[_type];
    prize = E_PRIZE[_type];
    // first position on road
    curPos = 0;
}
Enemy::~Enemy() {
    SDL_DestroyTexture(eTexture);
    eTexture = NULL;
}

void Enemy::updatePos(const vector<int> &dir, const vector<int> &xRoad, const vector<int> &yRoad) {
    if (curPos == xRoad.size()) {dstrect.x += speed; return;}
    switch (dir[curPos]) {
        case 0:
            dstrect.y -= speed;
            if (abs(dstrect.y + ENEMY_SIZE/2 - yRoad[curPos]*50-25 - PLAY_ZONE_Y) <= speed) {dstrect.y = yRoad[curPos]*50+25 + PLAY_ZONE_Y - ENEMY_SIZE/2; curPos++;}
            break;
        case 1:
            dstrect.x += speed;
            if (abs(dstrect.x + ENEMY_SIZE/2 - xRoad[curPos]*50-25 - PLAY_ZONE_X) <= speed) {dstrect.x = xRoad[curPos]*50+25 + PLAY_ZONE_X - ENEMY_SIZE/2; curPos++;}
            break;
        case 2:
            dstrect.y += speed;
            if (abs(dstrect.y + ENEMY_SIZE/2 - yRoad[curPos]*50-25 - PLAY_ZONE_Y) <= speed) {dstrect.y = yRoad[curPos]*50+25 + PLAY_ZONE_Y - ENEMY_SIZE/2; curPos++;}
            break;
        case 3:
            dstrect.x -= speed;
            if (abs(dstrect.x + ENEMY_SIZE/2 - xRoad[curPos]*50-25 - PLAY_ZONE_X) <= speed) {dstrect.x = xRoad[curPos]*50+25 + PLAY_ZONE_X - ENEMY_SIZE/2; curPos++;}
            break;
    }
}

void Enemy::drawToRender(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, eTexture, NULL, &dstrect);
}

int Enemy::getX() {return dstrect.x + ENEMY_SIZE/2;}
int Enemy::getY() {return dstrect.y + ENEMY_SIZE/2;}
int Enemy::getDam() {return damage;}
int Enemy::getPrize() {return prize;}

bool Enemy::getHit(double bX, double bY, int damamge) {
    if (sqrt((dstrect.x + ENEMY_SIZE/2 - bX)*(dstrect.x + ENEMY_SIZE/2 - bX) + (dstrect.y + ENEMY_SIZE/2 - bY)*(dstrect.y + ENEMY_SIZE/2 - bY)) <= ENEMY_SIZE/2 + BULLET_SIZE/2) {
        hp -= damamge;
        return true;
    }
    return false;
}

bool Enemy::isSuccess() {
    if (dstrect.x >= PLAY_ZONE_X + PLAY_ZONE_W) {
        return true;
    }
    return false;
}

bool Enemy::isDead() {
    if (hp <= 0) return true;
    else return false;
}