#include "gun.h"

Gun::Gun(SDL_Renderer* &gRenderer, double x, double y, int _type) {
    texture = loadTexture(gRenderer, GUN_PATH[_type]);
    type = _type;
    dstrect.x = x - GUN_SIZE/2; dstrect.y = y - GUN_SIZE/2;
    dstrect.h = GUN_SIZE; dstrect.w = GUN_SIZE;
    range = 100;

}
Gun::~Gun() {
    SDL_DestroyTexture(texture);
    texture = NULL;
}

double Gun::getX() {return dstrect.x;}
double Gun::getY() {return dstrect.y;}

void Gun::drawToRender(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, texture, NULL, &dstrect);
}

void Gun::setDamage(int k) {damage = k;}
int Gun::getDamage() {return damage;}

bool Gun::onShot(double x, double y) {
    if (sqrt((dstrect.x - x)*(dstrect.x - x) + (dstrect.y - y)*(dstrect.y - y)) <= range)
        return true;
    else return false;
}