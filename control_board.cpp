#include "control_board.h"

ctBoard::ctBoard(SDL_Renderer* &gRenderer) {
    cTexture = loadTexture(gRenderer, CT_BG);
    for (int i = 0; i < 6; i++) {
        gunTextures[i] = loadTexture(gRenderer, GUN_PATH[i]);
    }

    gunItemXPos[0] = 0; gunItemYPos[0] = 100;
    gunItemXPos[1] = 31; gunItemYPos[1] = 100;
    gunItemXPos[2] = 0; gunItemYPos[2] = 131;
    gunItemXPos[3] = 31; gunItemYPos[3] = 131;
    gunItemXPos[4] = 0; gunItemYPos[4] = 162;
    gunItemXPos[5] = 31; gunItemYPos[5] = 162;

}
ctBoard::~ctBoard() {
    for (int i = 0; i < 6; i++) {
        delete gunTextures[i];
        gunTextures[i] = NULL;
    }
}

void ctBoard::drawToRender(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, cTexture, NULL, NULL);
    dstrect.h = GUN_SIZE; dstrect.w = GUN_SIZE;
    for (int i = 0; i < 6; i++) {
        dstrect.x = gunItemXPos[i]; dstrect.y = gunItemYPos[i];
        SDL_RenderCopy(gRenderer, gunTextures[i], NULL, &dstrect);
    }
}

bool ctBoard::aGunItemChosen(int x, int y) {
    for (int i = 0; i < 6; i++) {
        if (x >= gunItemXPos[i] && x <= gunItemXPos[i] + GUN_SIZE && y >= gunItemYPos[i] && y <= gunItemYPos[i] + GUN_SIZE) {
            gunItemChosen = i;
            return true;
        }
    }
    return false;
}

void ctBoard::drawGunChosen(SDL_Renderer* &gRenderer, double x, double y) {
    SDL_Rect r;
    r.h = GUN_SIZE; r.w = GUN_SIZE;
    r.x = x - GUN_SIZE/2; r.y = y - GUN_SIZE/2;
    SDL_RenderCopy(gRenderer, gunTextures[gunItemChosen], NULL, &r);
}

int ctBoard::getTypeOfGunChosen() {return gunItemChosen;}