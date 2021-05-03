#include "base.h"

Base::Base(int y) {
    dstrect.x = PLAY_ZONE_X + PLAY_ZONE_W - 10;
    dstrect.y = y * 50 + PLAY_ZONE_Y - 10;
    dstrect.h = 70;
    dstrect.w = 10;
    hp = MAXHP;
}

Base::~Base() {}

void Base::setHP(int eHP) {hp -= eHP;}
void Base::drawGettingHitEffect(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    SDL_RenderCopy(gRenderer, gTexture->getHitTexture, NULL, NULL);
}

void Base::drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    SDL_RenderCopy(gRenderer, gTexture->baseTexture, NULL, &dstrect);
}

double Base::getHPRate() {return 1.0 * hp / MAXHP;}

bool Base::destroyed() {
    if (hp <= 0) return true;
    else return false;
}