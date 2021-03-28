#include "base.h"

Base::Base(SDL_Renderer* &gRenderer, int y) {
    texture = loadTexture(gRenderer, BASE_PATH);
    dstrect.x = PLAY_ZONE_X + PLAY_ZONE_W - 10;
    dstrect.y = y * 50 + PLAY_ZONE_Y - 10;
    dstrect.h = 70;
    dstrect.w = 10;
    hp = MAXHP;
}

Base::~Base() {
    SDL_DestroyTexture(texture);
    texture = NULL;
}

void Base::drawToRender(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, texture, NULL, &dstrect);
}

void Base::setHP(int eHP) {hp -= eHP;}
double Base::getHPRate() {return 1.0 * hp / MAXHP;}

bool Base::lose() {
    if (hp <= 0) return true;
    else return false;
}
