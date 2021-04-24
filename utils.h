#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"

void initSDL(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);
void quitSDL(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);
void logSDLError(const std::string &msg, bool fatal);
void waitUntilKeyPressed();

void treatPosition(double x, double y, int &row, int &col);

SDL_Texture* loadTexture(SDL_Renderer* &gRenderer, std::string path);

