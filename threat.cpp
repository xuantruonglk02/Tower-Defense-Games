#include "threat.h"

Threat::Threat(SDL_Renderer* &gRenderer, double x, double y) {
    mTexture = loadTexture(gRenderer, PLAYER_PATH);
    threatX = x;
    threatY = y;
}

Threat::~Threat() {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
}

SDL_Texture* Threat::getTexture() {return mTexture;}
double Threat::getX() {return threatX;}
double Threat::getY() {return threatY;}

void Threat::setX(double x) {
    if (x - PLAYER_SIZE/2 >= PLAY_ZONE_X && x + PLAYER_SIZE/2 <= PLAY_ZONE_X + PLAY_ZONE_W)
        threatX = x;
}

void Threat::setY(double y) {
    if (y - PLAYER_SIZE/2 >= PLAY_ZONE_Y && y + PLAYER_SIZE/2 <= PLAY_ZONE_Y + PLAY_ZONE_H)
        threatY = y;
}

void Threat::drawThreat(SDL_Renderer* &gRenderer) {
    SDL_Rect dstrect;
    dstrect.x = threatX - PLAYER_SIZE/2;
    dstrect.y = threatY - PLAYER_SIZE/2;
    dstrect.h = PLAYER_SIZE; dstrect.w = PLAYER_SIZE;
    SDL_RenderCopy(gRenderer, mTexture, NULL, &dstrect);
}