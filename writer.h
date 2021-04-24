#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

using std::string;

class Writer {
public:
    Writer();
    ~Writer();

    void setFont(int textSize, string _font = "fonts/comicbd.ttf");
    void setColorText(Uint8 r, Uint8 g, Uint8 b);
    
    SDL_Texture* loadTextTexture(SDL_Renderer* &gRenderer, string text, int &w, int &h);

private:
    TTF_Font* font = NULL;
    SDL_Texture* textTexture = NULL;
    SDL_Color textColor;
};