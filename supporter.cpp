#include "supporter.h"

Supporter::Supporter(int x, int y, int _type) {
    if (_type == 0) {
        max_frame = 9;
    } else {
        max_frame = 1;
    }

    centerPoint = {SUP_SIZE[_type]/2, SUP_SIZE[_type]/2};

    type = _type;
    buff = S_BUFF[_type];
    lever = 0;
    showRangeCircle = true;

    sX = (int)(x / 50) * 50 + 25;
    sY = (int)(y / 50) * 50 + 25;

    degree = 0;
    frame = 0;

    // base
    dstrect_bs.h = GUN_BASE_SIZE; dstrect_bs.w = GUN_BASE_SIZE;
    dstrect_bs.x = sX - dstrect_bs.w / 2; dstrect_bs.y = sY - dstrect_bs.h / 2;
    // supporter
    dstrect_s.x = sX - SUP_SIZE[type]/2; dstrect_s.y = sY - SUP_SIZE[type]/2;
    dstrect_s.h = SUP_SIZE[type]; dstrect_s.w = SUP_SIZE[type];
    // delete icon
    dstrect_d.w = TRASH_SIZE; dstrect_d.h = TRASH_SIZE;
    dstrect_d.x = sX - dstrect_d.w/2; dstrect_d.y = sY + GUN_BASE_SIZE/2 + 10;

    setRange(S_RANGE[_type]);

    timeID = SDL_GetTicks();

}

Supporter::~Supporter() {}

bool Supporter::clickOn() {
    if (!showRangeCircle) {
        showRangeCircle = true;
        return true;
    } else {
        showRangeCircle = false;
        return false;
    }
}

bool Supporter::checkClickOnTrashIcon(int x, int y) {
    if (sqrt((dstrect_d.x + dstrect_d.w/2 - x)*(dstrect_d.x + dstrect_d.w/2 - x) + (dstrect_d.y + dstrect_d.h/2 - y)*(dstrect_d.y + dstrect_d.h/2 - y)) <= TRASH_SIZE/2)
        return true;
    return false;
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

void Supporter::enableUpdate() {showRangeCircle = true;}
void Supporter::unenableUpdate() {showRangeCircle = false;}

void Supporter::drawToRenderer(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    SDL_RenderCopy(gRenderer, gTexture->baseSupporterTexture, NULL, &dstrect_bs);
    SDL_RenderCopyEx(gRenderer, gTexture->supporterTexture[type][frame], NULL, &dstrect_s, degree, &centerPoint, SDL_FLIP_NONE);

    if (SDL_GetTicks() - timeID >= 100) {
        frame++;
        if (frame == max_frame) frame = 0;
        timeID = SDL_GetTicks();
    }

    if (type == 1) degree += 3;
}

void Supporter::drawRangeCircle(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    if (showRangeCircle) {
        SDL_RenderCopy(gRenderer, gTexture->rangeCircleTexture, NULL, &dstrect_r);
        // draw trash icon
        SDL_RenderCopy(gRenderer, gTexture->trashTexture, NULL, &dstrect_d);
    }
}