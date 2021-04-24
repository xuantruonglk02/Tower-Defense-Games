#include "menu.h"

Menu::Menu(SDL_Renderer* &gRenderer) {
    menuTexture = loadTexture(gRenderer, MENU_PATH);
    oMenuTexture = loadTexture(gRenderer, O_MENU_PATH);
    pButtonTexture = loadTexture(gRenderer, PLAY_PATH);
    oButtonTexture = loadTexture(gRenderer, OPTIONS_PATH);
    qButtonTexture = loadTexture(gRenderer, QUIT_PATH);
    
    pX = 340; pY = 216;
    oX = 340; oY = 297;
    qX = 340; qY = 378;
}

Menu::~Menu() {
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(pButtonTexture);
    SDL_DestroyTexture(oButtonTexture);
    SDL_DestroyTexture(qButtonTexture);
    SDL_Texture* pButton = NULL;
    SDL_Texture* oButton = NULL;
    SDL_Texture* qButton = NULL;
}

void Menu::drawMenu(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, menuTexture, NULL, NULL);

    dstrect.h = BUTTON_H; dstrect.w = BUTTON_W;

    dstrect.x = pX; dstrect.y = pY;
    SDL_RenderCopy(gRenderer, pButtonTexture, NULL, &dstrect);

    dstrect.x = oX; dstrect.y = oY;
    SDL_RenderCopy(gRenderer, oButtonTexture, NULL, &dstrect);

    dstrect.x = qX; dstrect.y = qY;
    SDL_RenderCopy(gRenderer, qButtonTexture, NULL, &dstrect);
}

void Menu::optionsMenu(SDL_Renderer* &gRenderer, Sound* &sound) {
    SDL_Event e;
    // loop
    while (true) {
        // read event
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                // read click position
                int clickX, clickY;
                SDL_GetMouseState(&clickX, &clickY);

                // click on background music button
                if (sqrt((clickX - 425)*(clickX - 425) + (clickY - 325)*(clickY - 325)) <= 30) {
                    sound->musicInOptions();
                }

                // click on sound effect button
                else if (sqrt((clickX - 525)*(clickX - 525) + (clickY - 325)*(clickY - 325)) <= 30) {
                    sound->soundEffectInOptions();
                }
                // click on back button
                else if (clickX < 325 || clickX > 625 || clickY < 225 || clickY > 425) {
                    return;
                }
            }
        }

        // draw
        drawOptionsMenu(gRenderer);
        SDL_RenderPresent(gRenderer);
    }

}

void Menu::drawOptionsMenu(SDL_Renderer* &gRenderer) {
    dstrect.h = 200; dstrect.w = 300;
    dstrect.x = SCREEN_WIDTH/2 - 150;
    dstrect.y = SCREEN_HEIGHT/2 - 100;
    SDL_RenderCopy(gRenderer, oMenuTexture, NULL, &dstrect);
}

int Menu::clickOn(int x, int y) {
    // return 1 if click on play button
    if (x >= pX && x <= pX + BUTTON_W && y >= pY && y <= pY + BUTTON_H) return 1;
    // 2 - options button
    if (x >= oX && x <= oX + BUTTON_W && y >= oY && y <= oY + BUTTON_H) return 2;
    // 3 - quit button
    if (x >= qX && x <= qX + BUTTON_W && y >= qY && y <= qY + BUTTON_H) return 3;
}