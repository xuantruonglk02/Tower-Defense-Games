#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "config.h"
#include "utils.h"
#include "texture.h"
#include "menu.h"
#include "sound.h"
#include "control_board.h"
#include "map.h"
#include "base.h"
#include "wave.h"
#include "enemy.h"
#include "gun.h"
#include "supporter.h"
#include "bullet.h"
#include "writer.h"

using std::vector;
using std::to_string;

class Game {
public:
    void start();
    void setUp();
    void play();
    void endGame();
    // delete data game playing
    void clearGame();
    void quitGame();

    void addGun(double x, double y, int type);
    void addSupporter(double x, double y, int type);
    void addBullet(double gX, double gY, Enemy* &_enemy, int dmg, int type);
    
    void buffForGun(Supporter* &pSupporter);
    
    void waitingForNextWave();
    
    void callEnemy();

    void sortEnemyList();
    void eSwap(Enemy* &e1, Enemy* &e2);

    void freeFire();

    // remove
    void treatWhenEnemyGetHit();
    void treatWhenRocketBoom(Bullet* &rocket);
    void remoteEnemyDied();
    void removeEnemyFinished();
    void removeBulletOutScreen();

    void resetUpdateDisplay(Gun* const &pGun, Supporter* const &pSupporter);

    void renderCurrent();

    void drawMap();
    void drawControlBoard();
    void drawBase();
    void drawEnemy();
    void drawGun();
    void drawSupporter();
    void drawRange();
    void drawBullets();
    void drawUpdateBoard();

    void noticeWaveCurrent(int w);
    void showWaitTime();

private:
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;

    gameTexture* gTexture = NULL;

    Menu* menu = NULL;
    Sound* sound = NULL;
    // control board
    ctBoard* ctb = NULL;
    Map* map = NULL;
    Base* base = NULL;
    Writer* timeWriter = NULL;
    Writer* waveWriter = NULL;

    // wave
    vector <Wave> wave;
    int curWave, noticeWave;
    int waitTimeTransWave;
    int waitTimeCallEnemy;

    // gun
    vector<Gun*> guns;
    Gun* gunObject[150];
    // supporter
    vector<Supporter*> supporters;
    Supporter* supporterObject[150];

    // enemy
    vector<Enemy*> enemys;

    // bullet
    vector<Bullet*> bullets;

    SDL_Event e;
    Uint32 timeID;
    int mapOfObject[150];
    double mouseX, mouseY;
    int clickX, clickY;
    int row, col;
    int indexOfObject;
    bool readyForUpdate;
    bool dragging;
    bool callingEnemy;
    bool callNextWave;
    bool win;
    bool pause;
    bool quit;
};
