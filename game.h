#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "menu.h"
#include "player.h"
#include "threat.h"
#include "bullet.h"

using std::vector;

class Game {

public:
    // Starts up SDL and creates window
    void initSDL();
    // Free and quit SDL
    void quitSDL();
    // Show SDL error
    void logSDLError(const std::string& msg, bool fatal);

    // copy background texture to renderer
    void drawBackground(SDL_Texture* &gTexture);

    //
    void drawPauseButton();

    //
    void drawLaze(double pX, double pY, double mX, double mY);

    // add bullet to lít
    void addThreat();

    //
    void drawThreatList();

    // add bullet to list
    void addBullet(double pX, double pY, double mX, double mY);

    //
    void drawBulletList();

    //
    void removeBulletOutScreen();

    // get key for move
    void getKeyMove(SDL_Event &e ,bool &u, bool &r, bool &d, bool &l);

    //
    void handleCollision();

    // start game
    void start();
    // set up for game
    void setUp();
    // play game
    void play();
    // quit game
    void quitGame();

private:
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    
    // background texture
    SDL_Texture* bgTexture1 = NULL;
    SDL_Texture* bgTexture2 = NULL;
    // pause button
    SDL_Texture* psTexture = NULL;

    // menu
    Menu* menu = NULL;

    // player
    Player* player = NULL;

    // bullet
    vector <Bullet*> bullets;
    Bullet* pBullet = NULL;
    int bulletsSize = 0;

    // threat
    vector <Threat*> threats;
    Threat* pthreat = NULL;
    int threatsSize = 0;

    bool quit = false;
};