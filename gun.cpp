#include "gun.h"

Gun::Gun(SDL_Renderer* &gRenderer, double x, double y, int _type) {
    texture = loadTexture(gRenderer, GUN_PATH[_type]);
    type = _type;
    gX = x; gY = y;
    dstrect.x = x - GUN_SIZE/2; dstrect.y = y - GUN_SIZE/2;
    dstrect.h = GUN_SIZE; dstrect.w = GUN_SIZE;
    range = 150;
    damage = G_DAMAGE[_type];

}
Gun::~Gun() {
    SDL_DestroyTexture(texture);
    texture = NULL;
}

double Gun::getX() {return gX;}
double Gun::getY() {return gY;}

void Gun::drawToRender(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, texture, NULL, &dstrect);
}

void Gun::setDamage(int k) {damage = k;}
int Gun::getDamage() {return damage;}

bool Gun::onShot(double x, double y) {
    if (sqrt((gX - x)*(gX - x) + (gY - y)*(gY - y)) <= range)
        return true;
    else return false;
}