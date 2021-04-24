#include "control_board.h"

ctBoard::ctBoard(SDL_Renderer* &gRenderer) {
    cTexture = loadTexture(gRenderer, CTB_PATH);
    pTexture = loadTexture(gRenderer, PAUSE_PATH);
    lTexture = loadTexture(gRenderer, LOCK_PATH);
    hpbTexture = loadTexture(gRenderer, HPBAR_PATH);
    rTexture = loadTexture(gRenderer, SHOOTING_RANGE_CIRCLE_PATH);
    rvTexture = loadTexture(gRenderer, REVIEW_BOARD_PATH);
    for (int i = 0; i < 6; i++) {
        gunTextures[i] = loadTexture(gRenderer, TOWER_PATH[i]);
    }

    // set up position of 6 guns on control board
    gunItemXPos[0] = 30; gunItemYPos[0] = 210;
    gunItemXPos[1] = 80; gunItemYPos[1] = 210;
    gunItemXPos[2] = 30; gunItemYPos[2] = 260;
    gunItemXPos[3] = 80; gunItemYPos[3] = 260;
    gunItemXPos[4] = 30; gunItemYPos[4] = 310;
    gunItemXPos[5] = 80; gunItemYPos[5] = 310;

    // the first money
    gem = 2000;

    pause_ing = false;

    setUpWriterForMoney();

    SDL_SetTextureBlendMode(rTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(rTexture, 30);

}
ctBoard::~ctBoard() {
    SDL_DestroyTexture(cTexture);
    SDL_DestroyTexture(pTexture);
    SDL_DestroyTexture(hpbTexture);
    SDL_DestroyTexture(rTexture);
    cTexture = NULL;
    pTexture = NULL;
    hpbTexture = NULL;
    rTexture = NULL;
    for (int i = 0; i < 6; i++) {
        SDL_DestroyTexture(gunTextures[i]);
        gunTextures[i] = NULL;
    }
}

void ctBoard::setUpWriterForMoney() {
    writer = new Writer();
    writer->setFont(20);
    writer->setColorText(243, 156, 18);
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
    // draw money
    drawMoney(gRenderer);
}

void ctBoard::drawHPBar(SDL_Renderer* &gRenderer, double rate) {
    dstrect.h = 20; dstrect.w = (int)(rate * 484);
    dstrect.x = 284; dstrect.y = 50;
    SDL_RenderCopy(gRenderer, hpbTexture, NULL, &dstrect);
}

void ctBoard::drawGuns(SDL_Renderer* &gRenderer) {
    dstrect.h = GUN_BASE_SIZE; dstrect.w = GUN_BASE_SIZE;
    for (int i = 0; i < 4; i++) {
        dstrect.x = gunItemXPos[i]; dstrect.y = gunItemYPos[i];
        SDL_RenderCopy(gRenderer, gunTextures[i], NULL, &dstrect);
        // draw lock if money is not enough to buy gun
        if (G_PRICE[i] > gem) drawLocks(gRenderer, i);
    }
    for (int i = 4; i < 6; i++) {
        dstrect.x = gunItemXPos[i]; dstrect.y = gunItemYPos[i];
        SDL_RenderCopy(gRenderer, gunTextures[i], NULL, &dstrect);
        // draw lock if money is not enough to buy gun
        if (S_PRICE[i-4] > gem) drawLocks(gRenderer, i);
    }
}

void ctBoard::drawLocks(SDL_Renderer* &gRenderer, int i) {
    SDL_Rect r;
    r.w = 27; r.h = 40;
    r.x = gunItemXPos[i] + GUN_BASE_SIZE/2 - 13;
    r.y = gunItemYPos[i] + GUN_BASE_SIZE/2 - 20;
    SDL_RenderCopy(gRenderer, lTexture, NULL, &r);
}

void ctBoard::drawGunChosen(SDL_Renderer* &gRenderer, double x, double y) {
    SDL_Rect r;

    if (gunItemChosen > 3) {
        r.h = S_RANGE[gunItemChosen - 4] * 2; r.w = S_RANGE[gunItemChosen - 4] * 2;
        r.x = x - S_RANGE[gunItemChosen - 4]; r.y = y - S_RANGE[gunItemChosen - 4];
    } else {
        r.h = G_RANGE[gunItemChosen] * 2; r.w = G_RANGE[gunItemChosen] * 2;
        r.x = x - G_RANGE[gunItemChosen]; r.y = y - G_RANGE[gunItemChosen];
    }
    SDL_RenderCopy(gRenderer, rTexture, NULL, &r);

    r.h = GUN_BASE_SIZE; r.w = GUN_BASE_SIZE;
    r.x = x - GUN_BASE_SIZE/2; r.y = y - GUN_BASE_SIZE/2;
    SDL_RenderCopy(gRenderer, gunTextures[gunItemChosen], NULL, &r);
}

void ctBoard::drawMoney(SDL_Renderer* &gRenderer) {
    mTexture = writer->loadTextTexture(gRenderer, "$" + std::to_string(gem) , dstrect_money.w, dstrect_money.h);
    dstrect_money.x = 0; dstrect_money.y = 0;
    SDL_RenderCopy(gRenderer, mTexture, NULL, &dstrect_money);
}

void ctBoard::pauseMenu() {

}

void ctBoard::setGem(int k) {if (gem + k >= 0) gem += k;}
int ctBoard::getGem() {return gem;}
int ctBoard::getGemOfItemChosen() {
    if (gunItemChosen > 3) return S_PRICE[gunItemChosen - 4];
    return G_PRICE[gunItemChosen];
}


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
    for (int i = 0; i < 4; i++) {
        if (gem >= G_PRICE[i])
        if (x >= gunItemXPos[i] && x <= gunItemXPos[i] + GUN_BASE_SIZE && y >= gunItemYPos[i] && y <= gunItemYPos[i] + GUN_BASE_SIZE) {
            gunItemChosen = i;
            return true;
        }
    }
    for (int i = 4; i < 6; i++) {
        if (gem >= S_PRICE[i-4])
        if (x >= gunItemXPos[i] && x <= gunItemXPos[i] + GUN_BASE_SIZE && y >= gunItemYPos[i] && y <= gunItemYPos[i] + GUN_BASE_SIZE) {
            gunItemChosen = i;
            return true;
        }
    }
    return false;
}

int ctBoard::getTypeOfGunChosen() {return gunItemChosen;}

Uint32 ctBoard::getTimePause() {return timePause;}