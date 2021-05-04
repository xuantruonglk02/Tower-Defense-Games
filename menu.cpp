#include "menu.h"

Menu::Menu() {
    setDstRectButton(false);

    dstrect_om.w = OPTIONS_MENU_W; dstrect_om.h = OPTIONS_MENU_H;
    dstrect_om.x = SCREEN_WIDTH/2 - dstrect_om.w/2;
    dstrect_om.y = SCREEN_HEIGHT/2 - dstrect_om.h/2;

    dstrect_m_m.w = MUSIC_R * 2; dstrect_m_m.h = MUSIC_R * 2;
    dstrect_m_m.x = MUSIC_X + dstrect_om.x - MUSIC_R; dstrect_m_m.y = MUSIC_Y + dstrect_om.y - MUSIC_R;

    dstrect_m_s.w = MUSIC_R * 2; dstrect_m_s.h = MUSIC_R * 2;
    dstrect_m_s.x = SOUND_X + dstrect_om.x - MUSIC_R; dstrect_m_s.y = SOUND_Y + dstrect_om.y - MUSIC_R;

    dstrect_smm.w = SELECT_MAP_MENU_W; dstrect_smm.h = SELECT_MAP_MENU_H;
    dstrect_smm.x = SCREEN_WIDTH/2 - dstrect_smm.w/2; dstrect_smm.y = SCREEN_HEIGHT/2 - dstrect_smm.h/2;

}

Menu::~Menu() {}

void Menu::setDstRectButton(bool resume) {
    dstrect_p.w = BUTTON_W; dstrect_p.h = BUTTON_H;
    dstrect_p.x = SCREEN_WIDTH/2 - dstrect_p.w/2;

    dstrect_r.w = BUTTON_W; dstrect_r.h = BUTTON_H;
    dstrect_r.x = SCREEN_WIDTH/2 - dstrect_r.w/2;

    dstrect_sm.w = BUTTON_W; dstrect_sm.h = BUTTON_H;
    dstrect_sm.x = SCREEN_WIDTH/2 - dstrect_sm.w/2;

    dstrect_o.w = BUTTON_W; dstrect_o.h = BUTTON_H;
    dstrect_o.x = SCREEN_WIDTH/2 - dstrect_o.w/2;

    dstrect_q.w = BUTTON_W; dstrect_q.h = BUTTON_H;
    dstrect_q.x = SCREEN_WIDTH/2 - dstrect_q.w/2;

    if (resume) {
        dstrect_p.y = (SCREEN_HEIGHT - dstrect_p.h - dstrect_r.h - dstrect_o.h - dstrect_q.h - BUTTON_DISTANCE*3) / 2;
        dstrect_r.y = dstrect_p.y + dstrect_p.h + BUTTON_DISTANCE;
        dstrect_o.y = dstrect_r.y + dstrect_r.h + BUTTON_DISTANCE;
        dstrect_q.y = dstrect_o.y + dstrect_o.h + BUTTON_DISTANCE;
        
        dstrect_sm.y = SCREEN_HEIGHT;
    } else {
        dstrect_p.y = (SCREEN_HEIGHT - dstrect_p.h - dstrect_sm.h - dstrect_o.h - dstrect_q.h - BUTTON_DISTANCE*3) / 2;
        dstrect_sm.y = dstrect_p.y + dstrect_p.h + BUTTON_DISTANCE;        
        dstrect_o.y = dstrect_sm.y + dstrect_sm.h + BUTTON_DISTANCE;
        dstrect_q.y = dstrect_o.y + dstrect_o.h + BUTTON_DISTANCE;

        dstrect_r.y = SCREEN_HEIGHT;
    }
}

void Menu::drawMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    SDL_RenderCopy(gRenderer, gTexture->menuTexture, NULL, NULL);
    SDL_RenderCopy(gRenderer, gTexture->playButtonTexture, NULL, &dstrect_p);
    SDL_RenderCopy(gRenderer, gTexture->resumeButtonTexture, NULL, &dstrect_r);
    SDL_RenderCopy(gRenderer, gTexture->selectMapButtonTexture, NULL, &dstrect_sm);
    SDL_RenderCopy(gRenderer, gTexture->optionsButtonTexture, NULL, &dstrect_o);
    SDL_RenderCopy(gRenderer, gTexture->quitButtonTexture, NULL, &dstrect_q);
}

int Menu::clickOn(int x, int y) {
    // return 1 if click on play button
    if (x >= dstrect_p.x && x <= dstrect_p.x + dstrect_p.w && y >= dstrect_p.y && y <= dstrect_p.y + dstrect_p.h) return 1;
    // 2 - resume button
    if (x >= dstrect_r.x && x <= dstrect_r.x + dstrect_r.w && y >= dstrect_r.y && y <= dstrect_r.y + dstrect_r.h) return 2;
    // 3 - select map button
    if (x >= dstrect_sm.x && x <= dstrect_sm.x + dstrect_sm.w && y >= dstrect_sm.y && y <= dstrect_sm.y + dstrect_sm.h) return 3;
    // 4 - options button
    if (x >= dstrect_o.x && x <= dstrect_o.x + dstrect_o.w && y >= dstrect_o.y && y <= dstrect_o.y + dstrect_o.h) return 4;
    // 5 - quit button
    if (x >= dstrect_q.x && x <= dstrect_q.x + dstrect_q.w && y >= dstrect_q.y && y <= dstrect_q.y + dstrect_q.h) return 5;
}

void Menu::optionsMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture, Sound* &sound) {
    SDL_Event e;
    // loop
    while (true) {
        // draw
        drawOptionsMenu(gRenderer, gTexture, sound);
        SDL_RenderPresent(gRenderer);
        // read event
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                // read click position
                int clickX, clickY;
                SDL_GetMouseState(&clickX, &clickY);
                // click on background music button
                if (sqrt((clickX - dstrect_om.x - MUSIC_X)*(clickX - dstrect_om.x - MUSIC_X) + (clickY - dstrect_om.y - MUSIC_Y)*(clickY - dstrect_om.y - MUSIC_Y)) <= MUSIC_R) {
                    sound->clickOnMusicItem();
                }
                // click on sound effect button
                else if (sqrt((clickX - dstrect_om.x - SOUND_X)*(clickX - dstrect_om.x - SOUND_X) + (clickY - dstrect_om.y - SOUND_Y)*(clickY - dstrect_om.y - SOUND_Y)) <= MUSIC_R) {
                    sound->clickOnSoundItem();
                }
                // click on back button
                else if (clickX < dstrect_om.x || clickX > dstrect_om.x + dstrect_om.w || clickY < dstrect_om.y || clickY > dstrect_om.y + dstrect_om.h) {
                    return;
                }
            }
        }
    }
}

void Menu::drawOptionsMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture, Sound* &sound) {
    SDL_RenderCopy(gRenderer, gTexture->optionsMenuTexture, NULL, &dstrect_om);

    if (!sound->playingMusic()) SDL_RenderCopy(gRenderer, gTexture->muteTexture, NULL, &dstrect_m_m);
    if (!sound->playingSound()) SDL_RenderCopy(gRenderer, gTexture->muteTexture, NULL, &dstrect_m_s);
}

void Menu::selectMapMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture, Sound* &sound, int &indexOfMap) {
    SDL_Event e;
    while (true) {
        // draw
        SDL_RenderCopy(gRenderer, gTexture->selectMapMenuTexture, NULL, &dstrect_smm);
        SDL_RenderPresent(gRenderer);
        // read event
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                // read click position
                int clickX, clickY;
                SDL_GetMouseState(&clickX, &clickY);
                // select map
                for (int i = 0; i < MAP_NUM; i++)
                    if (clickX >= MAP_XY[i][0] + dstrect_smm.x && clickX <= MAP_XY[i][0] + dstrect_smm.x + MAP_REVIEW_W && clickY >= MAP_XY[i][1] + dstrect_smm.y && clickY <= MAP_XY[i][1] + dstrect_smm.y + MAP_REVIEW_H) {
                        sound->playClickSound();
                        indexOfMap = i;
                        return;
                    }
                // click on back button
                if (clickX < dstrect_smm.x || clickX > dstrect_smm.x + dstrect_smm.w || clickY < dstrect_smm.y || clickY > dstrect_smm.y + dstrect_smm.h) {
                    return;
                }
            }
        }
    }   
}