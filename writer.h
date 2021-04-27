#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "config.h"

using std::string;

class Writer {
public:
    Writer(string _font, int _size, Uint8 _r, Uint8 _g, Uint8 _b);
    ~Writer();

    void setColorText(Uint8 r, Uint8 g, Uint8 b);
    
    void writeText(SDL_Renderer* &gRenderer, string text, int _x, int _y);

private:
    void loadTextTexture(SDL_Renderer* &gRenderer, string text);

    TTF_Font* font = NULL;
    SDL_Texture* textTexture = NULL;
    SDL_Color textColor;
    SDL_Rect dstrect;
};