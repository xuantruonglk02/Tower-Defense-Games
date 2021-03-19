#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "config.h"
#include "utils.h"
#include "menu.h"
#include "control_board.h"
#include "enemy.h"
#include "gun.h"
#include "bullet.h"

using std::vector;

class Game {

public:
    void renderCurrent();
    // copy texture to renderer
    void drawMap();
    void drawControlBoard();
    void drawEnemy();
    void drawGun();
    void drawBullets();

    // add bullet to list
    void addGun(double x, double y, int type);
    // add a enemy
    void addEnemy();

    // fire
    void freeFire();

    // remove
    void removeBulletOutScreen();
    void removeEnemyFinished();

    // start game
    void start();
    // set up for game
    void setUp();
    // play game
    void play();
    // loser screen
    void endGame();
    // delete game playing
    void clearGame();
    // quit game
    void quitGame();

private:
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    
    // map texture
    SDL_Texture* mapTexture = NULL;

    // menu
    Menu* menu = NULL;

    // control board
    ctBoard* ctb = NULL;

    // enemy
    vector <Enemy*> enemys;
    int enemysSize;

    // gun
    vector <Gun*> guns;
    int gunsSize;

    // bullet
    vector <Bullet*> bullets;
    int bulletsSize;

    SDL_Event e;

    clock_t begin;

    double mouseX, mouseY;
    int clickX, clickY;
    bool mouseDown, dragging;

    bool quit;
};