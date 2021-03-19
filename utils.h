#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"

void initSDL(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);
void quitSDL(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);
void logSDLError(const std::string &msg, bool fatal);

SDL_Texture* loadTexture(SDL_Renderer* &renderer, std::string path);

void waitUntilKeyPressed();