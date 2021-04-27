#include "menu.h"

Menu::Menu() {
    dstrect_p.w = BUTTON_W; dstrect_p.h = BUTTON_H;
    dstrect_p.x = SCREEN_WIDTH/2 - dstrect_p.w/2;

    dstrect_o.w = BUTTON_W; dstrect_o.h = BUTTON_H;
    dstrect_o.x = SCREEN_WIDTH/2 - dstrect_o.w/2;

    dstrect_q.w = BUTTON_W; dstrect_q.h = BUTTON_H;
    dstrect_q.x = SCREEN_WIDTH/2 - dstrect_q.w/2;

    dstrect_p.y = (SCREEN_HEIGHT - dstrect_p.h - dstrect_o.h - dstrect_q.h - BUTTON_DISTANCE*2) / 2;
    dstrect_o.y = dstrect_p.y + dstrect_p.h + BUTTON_DISTANCE;
    dstrect_q.y = dstrect_o.y + dstrect_o.h + BUTTON_DISTANCE;

    dstrect_om.w = OPTIONS_MENU_W; dstrect_om.h = OPTIONS_MENU_H;
    dstrect_om.x = SCREEN_WIDTH/2 - dstrect_om.w/2;
    dstrect_om.y = SCREEN_HEIGHT/2 - dstrect_om.h/2;

    dstrect_m_m.w = MUSIC_R * 2; dstrect_m_m.h = MUSIC_R * 2;
    dstrect_m_m.x = MUSIC_X + dstrect_om.x - MUSIC_R; dstrect_m_m.y = MUSIC_Y + dstrect_om.y - MUSIC_R;

    dstrect_m_s.w = MUSIC_R * 2; dstrect_m_s.h = MUSIC_R * 2;
    dstrect_m_s.x = SOUND_X + dstrect_om.x - MUSIC_R; dstrect_m_s.y = SOUND_Y + dstrect_om.y - MUSIC_R;

    musicPlaying = true;
    soundPlaying = true;
}

Menu::~Menu() {}

void Menu::drawMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    SDL_RenderCopy(gRenderer, gTexture->menuTexture, NULL, NULL);

    SDL_RenderCopy(gRenderer, gTexture->playButtonTexture, NULL, &dstrect_p);
    SDL_RenderCopy(gRenderer, gTexture->optionsButtonTexture, NULL, &dstrect_o);
    SDL_RenderCopy(gRenderer, gTexture->quitButtonTexture, NULL, &dstrect_q);

}

void Menu::optionsMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture, Sound* &sound) {
    SDL_Event e;
    // loop
    while (true) {
        // draw
        drawOptionsMenu(gRenderer, gTexture);
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
                    musicPlaying = !musicPlaying;
                }
                // click on sound effect button
                else if (sqrt((clickX - dstrect_om.x - SOUND_X)*(clickX - dstrect_om.x - SOUND_X) + (clickY - dstrect_om.y - SOUND_Y)*(clickY - dstrect_om.y - SOUND_Y)) <= MUSIC_R) {
                    sound->clickOnSoundItem();
                    soundPlaying = !soundPlaying;
                }
                // click on back button
                else if (clickX < dstrect_om.x || clickX > dstrect_om.x + dstrect_om.w || clickY < dstrect_om.y || clickY > dstrect_om.y + dstrect_om.h) {
                    return;
                }
            }
        }
    }
}

void Menu::drawOptionsMenu(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    SDL_RenderCopy(gRenderer, gTexture->optionsMenuTexture, NULL, &dstrect_om);

    if (!musicPlaying) SDL_RenderCopy(gRenderer, gTexture->muteTexture, NULL, &dstrect_m_m);
    if (!soundPlaying) SDL_RenderCopy(gRenderer, gTexture->muteTexture, NULL, &dstrect_m_s);
}

int Menu::clickOn(int x, int y) {
    // return 1 if click on play button
    if (x >= dstrect_p.x && x <= dstrect_p.x + dstrect_p.w && y >= dstrect_p.y && y <= dstrect_p.y + dstrect_p.h) return 1;
    // 2 - options button
    if (x >= dstrect_o.x && x <= dstrect_o.x + dstrect_o.w && y >= dstrect_o.y && y <= dstrect_o.y + dstrect_o.h) return 2;
    // 3 - quit button
    if (x >= dstrect_q.x && x <= dstrect_q.x + dstrect_q.w && y >= dstrect_q.y && y <= dstrect_q.y + dstrect_q.h) return 3;
}