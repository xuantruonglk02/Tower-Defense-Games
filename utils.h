#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"

void initSDL(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);
void quitSDL(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);
void logSDLError(const std::string &msg, bool fatal);
void waitUntilKeyPressed();

//void loadTexture(SDL_Renderer* &gRenderer);
void treatPosition(double x, double y, int &row, int &col);

SDL_Texture* loadTexture(SDL_Renderer* &gRenderer, std::string path);

// SDL_Texture* menuTexture = NULL;
// SDL_Texture* pButtonbTexture = NULL;
// SDL_Texture* oButtonTexture = NULL;
// SDL_Texture* qButtonTexture = NULL;
// SDL_Texture* mapTexture = NULL;
// SDL_Texture* roadTexture = NULL;
// SDL_Texture* cbtTexture = NULL;
// SDL_Texture* gunTexture[] = {NULL, NULL, NULL, NULL, NULL, NULL};
// SDL_Texture* enemyTexture[] = {NULL, NULL, NULL};
// SDL_Texture* bulletTexture = NULL;
// SDL_Texture* pauseTexture = NULL;
// SDL_Texture* srCircleTexture = NULL;
