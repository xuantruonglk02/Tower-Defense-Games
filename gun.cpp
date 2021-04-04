#include "gun.h"

Gun::Gun(SDL_Renderer* &gRenderer, double x, double y, int _type) {
    // load gun texture
    gTexture = loadTexture(gRenderer, GUN_PATH[_type]);
    // use the first value array
    type = _type;
    range = G_RANGE[_type];
    damage = G_DAMAGE[_type];
    price = G_PRICE[_type];
    // gun position
    gX = (int)(x / 50) * 50 + 25;
    gY = (int)(y / 50) * 50 + 25;
    dstrect_g.x = gX - GUN_SIZE/2; dstrect_g.y = gY - GUN_SIZE/2;
    dstrect_g.h = GUN_SIZE; dstrect_g.w = GUN_SIZE;

    // load range shooting circle texture
    cTexture = loadTexture(gRenderer, SHOOTING_RANGE_CIRCLE_PATH);
    // circle position follow the gun position
    dstrect_c.h = 2 * G_RANGE[_type]; dstrect_c.w = 2 * G_RANGE[_type];
    dstrect_c.x = gX - dstrect_c.w / 2; dstrect_c.y = gY - dstrect_c.h / 2;
    // make the circle is transparent
    SDL_SetTextureBlendMode(cTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(cTexture, 30);
    // true when click on gun
    showCircle = false;

    // set up delay time
    shotDelayTime = G_SHOT_DELAY_TIME[_type];
    // start time counter
    timeID = SDL_GetTicks();
}
Gun::~Gun() {
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
}

void Gun::drawToRender(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, gTexture, NULL, &dstrect_g);
    // draw range shooting circle follow the gun when true
    if (showCircle) {
        SDL_RenderCopy(gRenderer, cTexture, NULL, &dstrect_c);
    }
}

void Gun::clickOn() {
    if (showCircle) showCircle = false;
    else showCircle = true;
}

void Gun::setRange(int r) {
    range = r;
    dstrect_c.h = 2*r; dstrect_c.w = 2*r;
    dstrect_c.x = gX - dstrect_c.w / 2; dstrect_c.y = gY - dstrect_c.h / 2;
}

void Gun::setDamage(int k) {damage = k;}
int Gun::getDamage() {return damage;}

void Gun::setTimeID() {timeID = SDL_GetTicks();}
Uint32 Gun::getTimeID() {return timeID;}
int Gun::getShotDelayTime() {return shotDelayTime;}

double Gun::getX() {return gX;}
double Gun::getY() {return gY;}

bool Gun::onShot(double x, double y) {
    if (sqrt((gX - x)*(gX - x) + (gY - y)*(gY - y)) <= range)
        return true;
    else return false;
}


