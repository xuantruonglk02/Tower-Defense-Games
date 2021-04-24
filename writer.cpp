#include "writer.h"

Writer::Writer() {
    TTF_Init();
}

Writer::~Writer() {
    TTF_CloseFont(font);
    SDL_DestroyTexture(textTexture);
    font = NULL;
    textTexture = NULL;
}

void Writer::setFont(int textSize, string _font) {
    font = TTF_OpenFont(_font.c_str(), textSize);
    if( font == NULL ) {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
}

void Writer::setColorText(Uint8 r, Uint8 g, Uint8 b) {
    textColor = {r, g, b};
}

SDL_Texture* Writer::loadTextTexture(SDL_Renderer* &gRenderer, string text, int &w, int &h) {
    SDL_Texture* mTexture = NULL;

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    // get width and height of text
    TTF_SizeText(font, text.c_str(), &w, &h);

    //Return success
    return mTexture;
}