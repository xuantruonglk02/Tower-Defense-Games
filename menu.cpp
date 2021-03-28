#include "menu.h"

Menu::Menu(SDL_Renderer* &gRenderer) {
    welcome = loadTexture(gRenderer, WELCOME_PATH);
    pButton = loadTexture(gRenderer, PLAY_PATH);
    oButton = loadTexture(gRenderer, OPTIONS_PATH);
    qButton = loadTexture(gRenderer, QUIT_PATH);
    
    pX = 367; pY = 216;
    oX = 367; oY = 297;
    qX = 367; qY = 378;
}

Menu::~Menu() {
    SDL_DestroyTexture(welcome);
    SDL_DestroyTexture(pButton);
    SDL_DestroyTexture(oButton);
    SDL_DestroyTexture(qButton);
    SDL_Texture* pButton = NULL;
    SDL_Texture* oButton = NULL;
    SDL_Texture* qButton = NULL;
}

void Menu::drawMenu(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, welcome, NULL, NULL);

    SDL_Rect dstrect;
    dstrect.h = BUTTON_H; dstrect.w = BUTTON_W;

    dstrect.x = pX; dstrect.y = pY;
    SDL_RenderCopy(gRenderer, pButton, NULL, &dstrect);

    dstrect.x = oX; dstrect.y = oY;
    SDL_RenderCopy(gRenderer, oButton, NULL, &dstrect);

    dstrect.x = qX; dstrect.y = qY;
    SDL_RenderCopy(gRenderer, qButton, NULL, &dstrect);
}

int Menu::clickOn(int x, int y) {
    if (x >= pX && x <= pX + BUTTON_W && y >= pY && y <= pY + BUTTON_H) return 1;
    if (x >= oX && x <= oX + BUTTON_W && y >= oY && y <= oY + BUTTON_H) return 2;
    if (x >= qX && x <= qX + BUTTON_W && y >= qY && y <= qY + BUTTON_H) return 3;
}

void Menu::option() {
    printf("option\n");
}