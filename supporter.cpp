#include "supporter.h"

Supporter::Supporter(SDL_Renderer* &gRenderer, int x, int y, int _type) {
    sTexture = loadTexture(gRenderer, SUPPORTER_PATH[_type]);
    type = _type;
    buff = S_BUFF[_type];
    lever = 0;
    showUpdate = true;

    sX = (int)(x / 50) * 50 + 25;
    sY = (int)(y / 50) * 50 + 25;

    dstrect_s.x = sX - GUN_BASE_SIZE/2; dstrect_s.y = sY - GUN_BASE_SIZE/2;
    dstrect_s.h = GUN_BASE_SIZE; dstrect_s.w = GUN_BASE_SIZE;

    rTexture = loadTexture(gRenderer, SHOOTING_RANGE_CIRCLE_PATH);
    setRange(S_RANGE[_type]);

    SDL_SetTextureBlendMode(rTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(rTexture, 30);

}
Supporter::~Supporter() {
    SDL_DestroyTexture(sTexture);
    SDL_DestroyTexture(rTexture);
    sTexture = NULL;
    rTexture = NULL;
}

bool Supporter::clickOn() {
    if (!showUpdate) {
        showUpdate = true;
        return true;
    } else {
        showUpdate = false;
        return false;
    }
}

int Supporter::checkClickOnUpdateButton(int x, int y, int gem) {
// buff = S_inc_buff
}

bool Supporter::inRange(int x, int y) {
    if (sqrt((sX - x)*(sX - x) + (sY - y)*(sY - y)) <= range) {
        return true;
    }
    return false;
}

int Supporter::getType() {return type;}
int Supporter::getBuff() {return buff;}

void Supporter::setRange(int r) {
    range = r;
    dstrect_r.h = r * 2; dstrect_r.w = r * 2;
    dstrect_r.x = sX - dstrect_r.w / 2;
    dstrect_r.y = sY - dstrect_r.h / 2;
}

void Supporter::enableUpdate() {showUpdate = true;}
void Supporter::unenableUpdate() {showUpdate = false;}

void Supporter::drawToRenderer(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, sTexture, NULL, &dstrect_s);
}

void Supporter::drawRangeCircle(SDL_Renderer* &gRenderer) {
    if (showUpdate)
        SDL_RenderCopy(gRenderer, rTexture, NULL, &dstrect_r);
}

void Supporter::drawUpdateBoard(SDL_Renderer* &gRenderer) {
    if (showUpdate) {

    }
}