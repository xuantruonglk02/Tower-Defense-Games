#include "game.h"

void Game::drawMap() {
    map->drawToRender(gRenderer);
}

void Game::drawControlBoard() {
    ctb->drawToRender(gRenderer, base->getHPRate());
}

void Game::drawBase() {
    base->drawToRender(gRenderer);
}

void Game::drawEnemy() {
    for (int i = 0; i < enemys.size(); i++) {
        enemys[i]->drawToRender(gRenderer);
        enemys[i]->updatePos(map->getDir(), map->getXRoad(), map->getYRoad());
    }
}

void Game::drawGun() {
    for (int i = 0; i < 150; i++) {
        if (gunObject[i] != nullptr) gunObject[i]->drawToRender(gRenderer);
    }
}

void Game::drawBullets() {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->drawToRender(gRenderer);
        bullets[i]->updatePos(0);
    }
}

void Game::noticeWaveCurrent() {
    //printf(" -wave %d\n", curWave+1);
}

void Game::waitingForNextWave() {
    if (wave[curWave].timeStarted == false) {
        wave[curWave].timeStarted = true;
        timeID = SDL_GetTicks();
        return;
    } else {
        if (SDL_GetTicks() - timeID >= waitTimeTransWave) {
            wave[curWave].started = true;
        }
    }
}

void Game::callEnemy() {
    if (wave[curWave].nextWave) {
        if (enemys.size() != 0) return;
        curWave++; return;
    }
    if (callingEnemy == false) {
        callingEnemy = true;
        timeID = SDL_GetTicks();
        return;
    } else {
        if (SDL_GetTicks() - timeID >= waitTimeCallEnemy) {
            enemys.push_back(new Enemy(gRenderer, map->getYFirst()*50+25 + PLAY_ZONE_Y, wave[curWave].nextEnemy()));
            timeID = SDL_GetTicks();
        }
    }
}

void Game::addGun(double x, double y, int type) {
    treatPosition(x, y, row, col);
    gunObject[row * 15 + col] = new Gun(gRenderer, x, y, type);
}

void Game::addBullet(double gX, double gY, double eX, double eY, int dmg) {
    double d = sqrt((eX - gX)*(eX - gX) + (eY - gY)*(eY - gY));
    bullets.push_back(new Bullet(gRenderer,
                                    gX, gY,
                                    (eX - gX) * (GUN_SIZE/2 + BULLET_SIZE/2) / d + gX,
                                    (eY - gY) * (GUN_SIZE/2 + BULLET_SIZE/2) / d + gY,
                                    GUN_SIZE/2 + BULLET_SIZE/2,
                                    dmg));
}

void Game::freeFire() {
    for (int i = 0; i < 150; i++) {
        if (gunObject[i] != nullptr)
        for (int j = 0; j < enemys.size(); j++) {
            if (enemys[j]->getX() + ENEMY_SIZE/2 >= PLAY_ZONE_X)
            if (gunObject[i]->onShot(enemys[j]->getX(), enemys[j]->getY())) {
                if (SDL_GetTicks() - gunObject[i]->getTimeID() >= gunObject[i]->getShotDelayTime()) {
                    addBullet(gunObject[i]->getX(), gunObject[i]->getY(), enemys[j]->getX(), enemys[j]->getY(), gunObject[i]->getDamage());
                    gunObject[i]->setTimeID();
                    break;
                }
            }
        }
    }
}

void Game::treatWhenEnemyGetHit() {
    for (int i = bullets.size()-1; i >= 0; i--) {
        for (int j = enemys.size()-1; j >= 0; j--) {
            if (enemys[j]->getHit(bullets[i]->getX(), bullets[i]->getY(), bullets[i]->getDamage())) {
                if (enemys[j]->isDead()) {
                    ctb->setGem(enemys[j]->getPrize());
                    delete enemys[j];
                    enemys.erase(enemys.begin() + j);
                }
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                break;
            }
        }
    }
}

void Game::remoteEnemyDied() {
    for (int i = enemys.size()-1; i >= 0; i--) {
        if (enemys[i]->isDead()) {
            delete enemys[i];
            enemys.erase(enemys.begin() + i);
        }
    }
}

void Game::removeBulletOutScreen() {
    for (int i = bullets.size()-1; i >= 0; i--) {
        if (bullets[i]->outOfScreen()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
}

void Game::removeEnemyFinished() {
    for (int i = enemys.size()-1; i >= 0; i--) {
        if (enemys[i]->isSuccess()) {
            base->setHP(enemys[i]->getDam());
            sound->playEffectSoundWhenGetHurt();
            delete enemys[i];
            enemys.erase(enemys.begin() + i);
        }
    }
}

void Game::start() {
    initSDL(gWindow, gRenderer);
    menu = new Menu(gRenderer);
    sound = new Sound();
    sound->playMusic();

    // loop menu
    while (true) {
        menu->drawMenu(gRenderer);
        SDL_RenderPresent(gRenderer);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                SDL_GetMouseState(&clickX, &clickY);
                switch (menu->clickOn(clickX, clickY)) {
                    case 1:
                        play();
                        break;
                    case 2:
                        menu->optionsMenu(gRenderer, sound);
                        break;
                    case 3:
                        quitGame();
                        return;
                }
            }
        }
    }
}

void Game::setUp() {
    ctb = new ctBoard(gRenderer);
    map = new Map(gRenderer);
    // read map from file
    map->readFromFile(quit);
    for (int i = 0; i < 150; i++) mapOfObject[i] = -2;
    // map of road
    map->buildMapOfObject(mapOfObject);

    // finish gate of enemy
    base = new Base(gRenderer, map->getYLast());
    // read enemy wave data from file
    readWaveData(wave, quit);

    for (int i = 0; i < 150; i++) gunObject[i] = NULL;

    // current wave
    curWave = 0;
    // delay time
    waitTimeTransWave = 5000;
    waitTimeCallEnemy = 700;

    callingEnemy = false;
    pause = false;
    win = false;
    quit = false;
}

void Game::renderCurrent() {
    drawMap();
    drawBase();
    noticeWaveCurrent();
    drawEnemy();
    drawGun();
    drawBullets();
    drawControlBoard();

    // render if grag a gun for attack
    if (mouseDown && ctb->aGunItemIsChosen(clickX, clickY)) {
        if (G_PRICE[ctb->getTypeOfGunChosen()] <= ctb->getGem()) {
            ctb->drawGunChosen(gRenderer, e.motion.x, e.motion.y);
            dragging = true;
        }
    }
}

void Game::play() {
    setUp();

    while (!quit) {
        // read event
        while (SDL_PollEvent(&e)) {
            // get mouse position
            if (e.motion.x >= 0 && e.motion.x <= SCREEN_WIDTH) mouseX = e.motion.x;
            if (e.motion.y >= 0 && e.motion.y <= SCREEN_HEIGHT) mouseY = e.motion.y;

            // get click event
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                mouseDown = true;
                SDL_GetMouseState(&clickX, &clickY);
                // when click on control board
                if (ctb->clickPauseButton(clickX, clickY))
                    if (pause) pause = false;
                    else pause = true;
                // when click on a gun on screen
                treatPosition(clickX, clickY, row, col);
                if (row > -1 && col > -1 && gunObject[row * 15 + col] != nullptr) gunObject[row * 15 + col]->clickOn();
            }
            // add gun when release left button
            if (dragging)
                if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = false;
                    dragging = false;
                    // check draw gun out of play zone
                    if (mouseX >= PLAY_ZONE_X && mouseX <= PLAY_ZONE_X + PLAY_ZONE_W && mouseY >= PLAY_ZONE_Y && mouseY <= PLAY_ZONE_Y + PLAY_ZONE_H) {
                        // check draw gun on road or other gun
                        int x = (int)(mouseY-PLAY_ZONE_Y) / 50, y = (int)(mouseX-PLAY_ZONE_X)/50;
                        if (mapOfObject[x * 15 + y] == -2) {
                            addGun(mouseX, mouseY, ctb->getTypeOfGunChosen());
                            mapOfObject[x * 15 + y] = ctb->getTypeOfGunChosen();
                            ctb->setGem(-G_PRICE[ctb->getTypeOfGunChosen()]);
                        }
                    }
                }
        }

        if (pause) continue;

        if (curWave == wave.size()) {
            win = true;
            break;
        } else {
            if (wave[curWave].started == false) waitingForNextWave();
            if (wave[curWave].started == true) callEnemy();
        }

        freeFire();

        treatWhenEnemyGetHit();

        remoteEnemyDied();
        removeBulletOutScreen();
        removeEnemyFinished();

        renderCurrent();

        if (base->destroyed()) {
            quit = true;
            win = false;
        }

        SDL_RenderPresent(gRenderer);
    }

    endGame();
}

void Game::endGame() {
    clearGame();
    if (win) printf(" win\n");
        else printf(" lose\n");
}

void Game::clearGame() {
    quit = false;
    delete ctb;
    delete map;
    delete base;
    ctb = NULL;
    map = NULL;
    base = NULL;
    wave.clear();
    enemys.clear();
    bullets.clear();
    for (int i = 0; i < 150; i++) {
        delete gunObject[i];
        gunObject[i] = NULL;
    }
}

void Game::quitGame() {
    //clearGame();
    delete sound;
    delete menu;
    sound = NULL;
    menu = NULL;
    quitSDL(gWindow, gRenderer);
    printf("quit\n");
}
