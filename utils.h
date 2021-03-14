#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

SDL_Texture* loadTexture(SDL_Renderer* &renderer, std::string path);

void waitUntilKeyPressed();