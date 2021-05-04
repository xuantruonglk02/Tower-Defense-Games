#include "control_board.h"

ctBoard::ctBoard() {

    //next button
    dstrect_nb.w = NEXT_BUTTON_W; dstrect_nb.h = NEXT_BUTTON_H;
    dstrect_nb.x = TOWER_BOARD_X;
    dstrect_nb.y = TOWER_BOARD_Y - DISTANCE - dstrect_nb.h;
    // pause menu
    dstrect_pm.w = OPTIONS_MENU_W; dstrect_pm.h = OPTIONS_MENU_H;
    dstrect_pm.x = SCREEN_WIDTH/2 - dstrect_pm.w/2;
    dstrect_pm.y = SCREEN_HEIGHT/2 - dstrect_pm.h/2;
    // mute
    dstrect_m_m.w = MUSIC_R * 2; dstrect_m_m.h = MUSIC_R * 2;
    dstrect_m_m.x = MUSIC_X + dstrect_pm.x - MUSIC_R; dstrect_m_m.y = MUSIC_Y + dstrect_pm.y - MUSIC_R;

    dstrect_m_s.w = MUSIC_R * 2; dstrect_m_s.h = MUSIC_R * 2;
    dstrect_m_s.x = SOUND_X + dstrect_pm.x - MUSIC_R; dstrect_m_s.y = SOUND_Y + dstrect_pm.y - MUSIC_R;
    // hp bar
    dstrect_hp.h = 20;
    dstrect_hp.x = 284; dstrect_hp.y = 50;
    // pause button
    dstrect_pb.h = 50; dstrect_pb.w = 50;
    dstrect_pb.x = 890; dstrect_pb.y = 10;
    // set up position of 6 guns on control board
    gunItemXPos[0] = 36 + TOWER_BOARD_X; gunItemYPos[0] = 32 + TOWER_BOARD_Y;
    gunItemXPos[1] = 94 + TOWER_BOARD_X; gunItemYPos[1] = 32 + TOWER_BOARD_Y;
    gunItemXPos[2] = 36 + TOWER_BOARD_X; gunItemYPos[2] = 85 + TOWER_BOARD_Y;
    gunItemXPos[3] = 94 + TOWER_BOARD_X; gunItemYPos[3] = 85 + TOWER_BOARD_Y;
    gunItemXPos[4] = 36 + TOWER_BOARD_X; gunItemYPos[4] = 138 +TOWER_BOARD_Y;
    gunItemXPos[5] = 94 + TOWER_BOARD_X; gunItemYPos[5] = 138 +TOWER_BOARD_Y;

    for (int i = 0; i < 6; i++) {
        dstrect_rvb[i].w = REVIEW_BOARD_SIZE[i][0];
        dstrect_rvb[i].h = REVIEW_BOARD_SIZE[i][1];
    }

    dstrect_l.w = LOCK_W; dstrect_l.h = LOCK_H;

    // the first money
    gem = FIRST_MONEY;

    setUpWriterForMoney();

}
ctBoard::~ctBoard() {
    delete writer;
    writer = NULL;
}

void ctBoard::setUpWriterForMoney() {
    writer = new Writer("fonts/comicbd.ttf", 20, 243, 156, 18);
}

bool ctBoard::aTowerIsChosen(int x, int y) {
    for (int i = 0; i < 4; i++) {
        if (gem >= G_PRICE[i])
        if (sqrt((x - gunItemXPos[i])*(x - gunItemXPos[i]) + (y - gunItemYPos[i])*(y - gunItemYPos[i])) <= GUN_BASE_SIZE/2) {
            gunItemChosen = i;
            return true;
        }
    }
    for (int i = 4; i < 6; i++) {
        if (gem >= S_PRICE[i-4])
        if (sqrt((x - gunItemXPos[i])*(x - gunItemXPos[i]) + (y - gunItemYPos[i])*(y - gunItemYPos[i])) <= GUN_BASE_SIZE/2) {
            gunItemChosen = i;
            return true;
        }
    }
    return false;
}

int ctBoard::getTypeOfGunChosen() {return gunItemChosen;}

void ctBoard::drawTowerChosen(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double x, double y) {
    SDL_Rect r;

    if (gunItemChosen > 3) {
        r.h = S_RANGE[gunItemChosen - 4] * 2; r.w = S_RANGE[gunItemChosen - 4] * 2;
        r.x = x - S_RANGE[gunItemChosen - 4]; r.y = y - S_RANGE[gunItemChosen - 4];
    } else {
        r.h = G_RANGE[gunItemChosen] * 2; r.w = G_RANGE[gunItemChosen] * 2;
        r.x = x - G_RANGE[gunItemChosen]; r.y = y - G_RANGE[gunItemChosen];
    }
    SDL_RenderCopy(gRenderer, gTexture->rangeCircleTexture, NULL, &r);

    r.h = GUN_BASE_SIZE; r.w = GUN_BASE_SIZE;
    r.x = x - GUN_BASE_SIZE/2; r.y = y - GUN_BASE_SIZE/2;
    SDL_RenderCopy(gRenderer, gTexture->towerTexture[gunItemChosen], NULL, &r);
}

void ctBoard::drawReviewBoard(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double x, double y) {
    for (int i = 0; i < 6; i++)
        if (sqrt((x - gunItemXPos[i])*(x - gunItemXPos[i]) + (y - gunItemYPos[i])*(y - gunItemYPos[i])) <= GUN_BASE_SIZE/2) {
            dstrect_rvb[i].x = x;
            dstrect_rvb[i].y = y;
            SDL_RenderCopy(gRenderer, gTexture->reviewBoardTexture[i], NULL, &dstrect_rvb[i]);
            break;
        }
}

void ctBoard::setGem(int k) {
    if (gem + k >= 0) gem += k;
    if (gem > 99999) gem = 99999;
}
int ctBoard::getGem() {return gem;}
int ctBoard::getGemOfItemChosen() {
    if (gunItemChosen > 3) return S_PRICE[gunItemChosen - 4];
    return G_PRICE[gunItemChosen];
}

Uint32 ctBoard::getTimePause() {return SDL_GetTicks() - startPause;}

bool ctBoard::clickPauseButton(int x, int y) {
    if (x >= 890 && x <= 940 && y >= 10 && y <= 60) {
        startPause = SDL_GetTicks();
        return true;
    }
    return false;
}

void ctBoard::pauseMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture, Sound* &sound, bool &resume) {
    SDL_Event e;
    while (true) {
        SDL_RenderCopy(gRenderer, gTexture->pauseMenuTexture, NULL, &dstrect_pm);
        if (!sound->playingMusic()) SDL_RenderCopy(gRenderer, gTexture->muteTexture, NULL, &dstrect_m_m);
        if (!sound->playingSound()) SDL_RenderCopy(gRenderer, gTexture->muteTexture, NULL, &dstrect_m_s);
        SDL_RenderPresent(gRenderer);
        // read event
        int clickX, clickY;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                SDL_GetMouseState(&clickX, &clickY);

                if (sqrt((clickX - MUSIC_X - dstrect_pm.x)*(clickX - MUSIC_X - dstrect_pm.x) + (clickY - MUSIC_Y - dstrect_pm.y)*(clickY - MUSIC_Y - dstrect_pm.y)) <= MUSIC_R) {
                    sound->playClickSound();
                    sound->clickOnMusicItem();
                }

                if (sqrt((clickX - SOUND_X - dstrect_pm.x)*(clickX - SOUND_X - dstrect_pm.x) + (clickY - SOUND_Y - dstrect_pm.y)*(clickY - SOUND_Y - dstrect_pm.y)) <= MUSIC_R) {
                    sound->playClickSound();
                    sound->clickOnSoundItem();
                }

                if (clickX >= BACK_BUTTON_X + dstrect_pm.x && clickX <= BACK_BUTTON_X + dstrect_pm.x + BACK_BUTTON_W && clickY >= BACK_BUTTON_Y + dstrect_pm.y && clickY <= BACK_BUTTON_Y + dstrect_pm.y + BACK_BUTTON_H) {
                    sound->playClickSound();
                    resume = true;
                    return;
                }

                else if (clickX < dstrect_pm.x || clickX > dstrect_pm.x + dstrect_pm.w || clickY < dstrect_pm.y || clickY > dstrect_pm.y + dstrect_pm.h) {
                    resume = false;
                    return;
                }
            }
        }
    }
}

bool ctBoard::clickNextButton(int x, int y) {
    if (x >= dstrect_nb.x && x < dstrect_nb.x + dstrect_nb.w && y >= dstrect_nb.y && y < dstrect_nb.y + dstrect_nb.h)
        return true;
    return false;
}

void ctBoard::drawNextButton(SDL_Renderer* &gRenderer, gameTexture* &gTexture, int k) {
    SDL_RenderCopy(gRenderer, gTexture->nextButtonTexture[k], NULL, &dstrect_nb);
}

void ctBoard::drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double rate) {
    // draw control board background
    SDL_RenderCopy(gRenderer, gTexture->controlBoardTexture, NULL, NULL);
    // draw pause button
    SDL_RenderCopy(gRenderer, gTexture->pauseButtonTexture, NULL, &dstrect_pb);
    // draw hp bar
    drawHPBar(gRenderer, gTexture, rate);
    // draw 6 guns
    drawGuns(gRenderer, gTexture);
    // draw money
    drawMoney(gRenderer);
}

void ctBoard::drawHPBar(SDL_Renderer* &gRenderer, gameTexture* &gTexture, double rate) {
    dstrect_hp.w = (int)(rate * 484);
    SDL_RenderCopy(gRenderer, gTexture->hpBarTexture, NULL, &dstrect_hp);
}

void ctBoard::drawGuns(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    for (int i = 0; i < 4; i++) {
        if (G_PRICE[i] > gem) drawLocks(gRenderer, gTexture, i);
    }
    for (int i = 4; i < 6; i++) {
        if (S_PRICE[i-4] > gem) drawLocks(gRenderer, gTexture, i);
    }
}

void ctBoard::drawLocks(SDL_Renderer* &gRenderer, gameTexture* &gTexture, int i) {
    dstrect_l.x = gunItemXPos[i] - dstrect_l.w/2;
    dstrect_l.y = gunItemYPos[i] - dstrect_l.h/2;
    SDL_RenderCopy(gRenderer, gTexture->lockGunTexture, NULL, &dstrect_l);
}

void ctBoard::drawMoney(SDL_Renderer* &gRenderer) {
    writer->writeText(gRenderer, "$" + std::to_string(gem), 10, 4);
}