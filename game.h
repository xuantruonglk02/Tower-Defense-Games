#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "config.h"
#include "utils.h"
#include "menu.h"
#include "sound.h"
#include "control_board.h"
#include "map.h"
#include "base.h"
#include "wave.h"
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
    void drawBase();
    void drawEnemy();
    void drawGun();
    void drawBullets();
    void noticeWaveCurrent();

    // delay time for 
    void waitingForNextWave();

    // call enemy
    void callEnemy();
    // add bullet to list
    void addGun(double x, double y, int type);
    // fire
    void freeFire();
    // fire
    void addBullet(double gX, double gY, double eX, double eY, int dmg);


    // remove
    void treatWhenEnemyGetHit();
    void remoteEnemyDied();
    void removeBulletOutScreen();
    void removeEnemyFinished();

    // start game
    void start();
    // set up for game
    void setUp();
    // play game
    void play();
    // 
    void endGame();
    // delete game playing
    void clearGame();
    // quit game
    void quitGame();

private:
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;

    // menu
    Menu* menu = NULL;
    // sound
    Sound* sound = NULL;
    // control board
    ctBoard* ctb = NULL;
    // map
    Map* map = NULL;
    // base
    Base* base = NULL;

    // wave
    vector <Wave> wave;
    int curWave;
    int waitTimeTransWave;
    int waitTimeCallEnemy;

    // enemy
    vector <Enemy*> enemys;

    // gun
    Gun* gunObject[150];
    
    // bullet
    vector <Bullet*> bullets;

    SDL_Event e;
    Uint32 timeID;
    int mapOfObject[150];
    double mouseX, mouseY;
    int clickX, clickY;
    int row, col;
    bool mouseDown, dragging;
    bool callingEnemy;
    bool win;
    bool pause;
    bool quit;
};