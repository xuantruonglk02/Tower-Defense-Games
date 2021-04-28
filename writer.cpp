#include "writer.h"

Writer::Writer(string _font, int _size, Uint8 _r, Uint8 _g, Uint8 _b) {
    TTF_Init();
    
    font = TTF_OpenFont(_font.c_str(), _size);
    if( font == NULL ) {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    textColor = {_r, _g, _b};
}

Writer::~Writer() {
    TTF_CloseFont(font);
    SDL_DestroyTexture(textTexture);
    font = NULL;
    textTexture = NULL;
}

void Writer::setColorText(Uint8 r, Uint8 g, Uint8 b) {
    textColor = {r, g, b};
}

void Writer::writeText(SDL_Renderer* &gRenderer, string text, int _x, int _y) {
    loadTextTexture(gRenderer, text);
    if (_x == -1) dstrect.x = PLAY_ZONE_X/2 - dstrect.w/2;
    else dstrect.x = _x;
    dstrect.y = _y;
    SDL_RenderCopy(gRenderer, textTexture, NULL, &dstrect);
    SDL_DestroyTexture(textTexture);
}

void Writer::loadTextTexture(SDL_Renderer* &gRenderer, string text) {

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        textTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( textTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    // get width and height of text
    TTF_SizeText(font, text.c_str(), &dstrect.w, &dstrect.h);

}
