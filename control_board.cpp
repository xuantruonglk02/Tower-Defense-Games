#include "control_board.h"

ctBoard::ctBoard(SDL_Renderer* &gRenderer) {
    cTexture = loadTexture(gRenderer, CTB_PATH);
    pTexture = loadTexture(gRenderer, PAUSE_PATH);
    lTexture = loadTexture(gRenderer, LOCK_PATH);
    hpbTexture = loadTexture(gRenderer, HPBAR_PATH);
    for (int i = 0; i < 6; i++) {
        gunTextures[i] = loadTexture(gRenderer, GUN_PATH[i]);
    }

    // set up position of 6 guns on control board
    gunItemXPos[0] = 30; gunItemYPos[0] = 210;
    gunItemXPos[1] = 80; gunItemYPos[1] = 210;
    gunItemXPos[2] = 30; gunItemYPos[2] = 260;
    gunItemXPos[3] = 80; gunItemYPos[3] = 260;
    gunItemXPos[4] = 30; gunItemYPos[4] = 310;
    gunItemXPos[5] = 80; gunItemYPos[5] = 310;

    // the first money
    gem = 2;

    pause_ing = false;
}
ctBoard::~ctBoard() {
    SDL_DestroyTexture(cTexture);
    SDL_DestroyTexture(pTexture);
    SDL_DestroyTexture(hpbTexture);
    cTexture = NULL;
    pTexture = NULL;
    hpbTexture = NULL;
    for (int i = 0; i < 6; i++) {
        SDL_DestroyTexture(gunTextures[i]);
        gunTextures[i] = NULL;
    }
}

void ctBoard::drawToRender(SDL_Renderer* &gRenderer, double rate) {
    // draw control board background
    SDL_RenderCopy(gRenderer, cTexture, NULL, NULL);
    // draw pause button
    dstrect.h = 50; dstrect.w = 50;
    dstrect.x = 890; dstrect.y = 10;
    SDL_RenderCopy(gRenderer, pTexture, NULL, &dstrect);
    // draw hp bar
    drawHPBar(gRenderer, rate);
    // draw 6 guns
    drawGuns(gRenderer);
}

void ctBoard::drawHPBar(SDL_Renderer* &gRenderer, double rate) {
    dstrect.h = 20; dstrect.w = (int)(rate * 484);
    dstrect.x = 284; dstrect.y = 50;
    SDL_RenderCopy(gRenderer, hpbTexture, NULL, &dstrect);
}

void ctBoard::drawGuns(SDL_Renderer* &gRenderer) {
    dstrect.h = GUN_SIZE; dstrect.w = GUN_SIZE;
    for (int i = 0; i < 6; i++) {
        dstrect.x = gunItemXPos[i]; dstrect.y = gunItemYPos[i];
        SDL_RenderCopy(gRenderer, gunTextures[i], NULL, &dstrect);
        // draw lock if money is not enough to buy gun
        if (G_PRICE[i] > gem) drawLocks(gRenderer, i);
    }
}

void ctBoard::drawLocks(SDL_Renderer* &gRenderer, int i) {
    SDL_Rect r;
    r.w = 27; r.h = 40;
    r.x = gunItemXPos[i] + GUN_SIZE/2 - 13;
    r.y = gunItemYPos[i] + GUN_SIZE/2 - 20;
    SDL_RenderCopy(gRenderer, lTexture, NULL, &r);
}

void ctBoard::drawGunChosen(SDL_Renderer* &gRenderer, double x, double y) {
    SDL_Rect r;
    r.h = GUN_SIZE; r.w = GUN_SIZE;
    r.x = x - GUN_SIZE/2; r.y = y - GUN_SIZE/2;
    SDL_RenderCopy(gRenderer, gunTextures[gunItemChosen], NULL, &r);
}

void ctBoard::pauseMenu() {

}

void ctBoard::setGem(int k) {if (gem + k >= 0) gem += k;}
int ctBoard::getGem() {return gem;}

bool ctBoard::clickPauseButton(int x, int y) {
    if (x >= 890 && x <= 940 && y >= 10 && y <= 60) {
        if (!pause_ing) {
            pause_ing = true;
            startPause = SDL_GetTicks();
        } else {
            pause_ing = false;
            timePause = SDL_GetTicks() - startPause;
        }
        pauseMenu();
        return true;
    }
    else return false;
}

bool ctBoard::aGunItemIsChosen(int x, int y) {
    for (int i = 0; i < 6; i++) {
        if (x >= gunItemXPos[i] && x <= gunItemXPos[i] + GUN_SIZE && y >= gunItemYPos[i] && y <= gunItemYPos[i] + GUN_SIZE) {
            gunItemChosen = i;
            return true;
        }
    }
    return false;
}

int ctBoard::getTypeOfGunChosen() {return gunItemChosen;}

Uint32 ctBoard::getTimePause() {return timePause;}