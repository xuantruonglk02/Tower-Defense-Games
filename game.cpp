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
    for (int i = 0; i < guns.size(); i++) {
        guns[i]->drawToRender(gRenderer);
    }
    
}

void Game::drawSupporter() {
    for (int i = 0; i < supporters.size(); i++) {
        supporters[i]->drawToRenderer(gRenderer);
    }
}

void Game::drawRange() {
    for (int i = 0; i < guns.size(); i++) {
        guns[i]->drawRangeCircle(gRenderer);
    }
    for (int i = 0; i < supporters.size(); i++) {
        supporters[i]->drawRangeCircle(gRenderer);
    }
}

void Game::drawBullets() {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->drawToRender(gRenderer);
    }
}

void Game::drawUpdateBoard() {
    for (int i = 0; i < guns.size(); i++) {
        guns[i]->drawUpdateBoard(gRenderer);
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
    if (gunObject[row * 15 + col] != nullptr) return;
    gunObject[row * 15 + col] = new Gun(gRenderer, x, y, type);
    guns.push_back(gunObject[row * 15 + col]);

}

void Game::addSupporter(double x, double y, int type) {
    treatPosition(x, y, row, col);
    if (supporterObject[row * 15 + col] != nullptr) return;
    supporterObject[row * 15 + col] = new Supporter(gRenderer, x, y, type);
    supporters.push_back(supporterObject[row * 15 + col]);

    buffForGun(supporters[supporters.size()-1]);
}

void Game::addBullet(double gX, double gY, Enemy* &_enemy, int dmg, int type) {
    bullets.push_back(new Bullet(gRenderer, gX, gY, _enemy, dmg, type));
}

void Game::buffForGun(Supporter* pSupporter) {
    for (int i = 0; i < guns.size(); i++)
        if (pSupporter->inRange(guns[i]->getX(), guns[i]->getY())) guns[i]->setBuff(pSupporter->getType(), pSupporter->getBuff());
}

void Game::freeFire() {
    for (int i = 0; i < guns.size(); i++) {
        for (int j = 0; j < enemys.size(); j++) {
            if (enemys[j]->getX() + ENEMY_SIZE/2 >= PLAY_ZONE_X)
            if (guns[i]->onShot(enemys[j]->getX(), enemys[j]->getY())) {
                guns[i]->changeShotDirection(enemys[j]->getX(), enemys[j]->getY());
                if (SDL_GetTicks() - guns[i]->getTimeID() >= guns[i]->getShotDelayTime()) {
                    addBullet(guns[i]->getX(), guns[i]->getY(), enemys[j], guns[i]->getDamage(), guns[i]->getType());
                    guns[i]->setTimeID();
                    guns[i]->fire();
                }
                break;
            }
        }
    }
}

void Game::resetUpdateDisplay(Gun* pGun, Supporter* pSupporter) {
    for (int i = 0; i < guns.size(); i++)
        if (guns[i] != pGun) guns[i]->unenableUpdate();
    for (int i = 0; i < supporters.size(); i++)
        if (supporters[i] != pSupporter) supporters[i]->unenableUpdate();
}

void Game::treatWhenEnemyGetHit() {
    for (int i = bullets.size()-1; i >= 0; i--) {
        for (int j = enemys.size()-1; j >= 0; j--) {
            // rocket not boom if doesn't meet target
            if (bullets[i]->getType() == 3 && bullets[i]->getTarget() != enemys[j]) {
                if (j == 0) bullets[i]->targetKilled();
                continue;
            }

            if ((bullets[i]->getType() == 2 && enemys[j]->getHit(bullets[i]->getLastX(), bullets[i]->getLastY(), bullets[i]->getDamage(), bullets[i]->getType()))
                || (bullets[i]->getType() != 2 && enemys[j]->getHit(bullets[i]->getX(), bullets[i]->getY(), bullets[i]->getDamage(), bullets[i]->getType()))) {
                
                if (bullets[i]->getType() == 3) treatWhenRocketBoom(bullets[i]);
                if (enemys[j]->isDead()) bullets[i]->targetKilled();
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                break;
            }
        }
        
    }
}

void Game::treatWhenRocketBoom(Bullet* rocket) {
    for (int i = 0; i < enemys.size(); i++) {
        enemys[i]->getBoom(rocket->getX(), rocket->getY(), rocket->getDamage());
    }
}

void Game::remoteEnemyDied() {
    for (int i = enemys.size()-1; i >= 0; i--) {
        if (enemys[i]->isDead()) {
            ctb->setGem(enemys[i]->getPrize());
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
    //sound->playMusic();

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

    map->readFromFile(quit);

    for (int i = 0; i < 150; i++) mapOfObject[i] = -2;
    map->buildMapOfObject(mapOfObject);

    base = new Base(gRenderer, map->getYLast());

    readWaveData(wave, quit);

    for (int i = 0; i < 150; i++) {gunObject[i] = NULL; supporterObject[i] = NULL;}

    curWave = 0;

    waitTimeTransWave = 7000;
    waitTimeCallEnemy = 700;

    callingEnemy = false;
    pause = false;
    win = false;
    quit = false;

    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
}

void Game::renderCurrent() {
    drawMap();
    drawBase();
    noticeWaveCurrent();
    drawEnemy();
    drawGun();
    drawSupporter();
    drawRange();
    drawBullets();
    drawControlBoard();
    drawUpdateBoard();

    if (dragging) {
        if (ctb->getGemOfItemChosen() <= ctb->getGem()) {
            ctb->drawGunChosen(gRenderer, e.motion.x, e.motion.y);
        }
    }
}

void Game::play() {
    setUp();

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                clearGame();
                return;
            }

            if (e.motion.x >= 0 && e.motion.x <= SCREEN_WIDTH) mouseX = e.motion.x;
            if (e.motion.y >= 0 && e.motion.y <= SCREEN_HEIGHT) mouseY = e.motion.y;

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                SDL_GetMouseState(&clickX, &clickY);

                if (ctb->clickPauseButton(clickX, clickY))
                    if (!pause) pause = true;
                    else {
                        pause = false;
                        timeID += ctb->getTimePause();
                    }

                if (ctb->aGunItemIsChosen(clickX, clickY)) {
                    dragging = true;
                    resetUpdateDisplay(NULL, NULL);
                }

                treatPosition(clickX, clickY, row, col);
                if (row > -1 && col > -1) {
                    if (gunObject[row * 15 + col] != nullptr) {
                        if (gunObject[row * 15 + col]->clickOn()) {  
                            resetUpdateDisplay(gunObject[row * 15 + col], NULL);
                            readyForUpdate = true;
                            indexOfGunObject = row * 15 + col;
                        } else {
                            readyForUpdate = false;
                        }
                    } else if (supporterObject[row * 15 + col] != nullptr) {
                        if (supporterObject[row * 15 + col]->clickOn()) {
                            resetUpdateDisplay(NULL, supporterObject[row * 15 + col]);
                        }
                    } else resetUpdateDisplay(NULL, NULL);
                }

                if (readyForUpdate) {
                    ctb->setGem(-(gunObject[indexOfGunObject]->checkClickOnUpdateButton(clickX, clickY, ctb->getGem())));
                }
            }

            if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                // add gun when release left button
                if (dragging) {
                    dragging = false;
                    // check draw gun out of play zone
                    if (mouseX >= PLAY_ZONE_X && mouseX <= PLAY_ZONE_X + PLAY_ZONE_W && mouseY >= PLAY_ZONE_Y && mouseY <= PLAY_ZONE_Y + PLAY_ZONE_H) {
                        // check draw gun on road or other gun
                        treatPosition(mouseX, mouseY, row, col);
                        if (mapOfObject[row * 15 + col] == -2) {
                            if (ctb->getTypeOfGunChosen() < 4)
                                addGun(mouseX, mouseY, ctb->getTypeOfGunChosen());
                            else
                                addSupporter(mouseX, mouseY, ctb->getTypeOfGunChosen() - 4);
                            mapOfObject[row * 15 + col] = ctb->getTypeOfGunChosen();
                            ctb->setGem(-ctb->getGemOfItemChosen());
                        }
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

        renderCurrent();

        treatWhenEnemyGetHit();

        remoteEnemyDied();
        removeBulletOutScreen();
        removeEnemyFinished();

        if (base->destroyed()) {
            quit = true;
            win = false;
        }

        SDL_RenderPresent(gRenderer);
    }

    endGame();
}

void Game::endGame() {

    SDL_Texture* endScreenTexture = NULL;
    if (win) {
        endScreenTexture = loadTexture(gRenderer, "images/win.png");
    } else {
        endScreenTexture = loadTexture(gRenderer, "images/lose.png");
    }

    SDL_Rect r;
    r.h = 200; r.w = 400;
    r.x = SCREEN_WIDTH/2 - 200;
    r.y = SCREEN_HEIGHT/2 - 100;

    SDL_RenderCopy(gRenderer, endScreenTexture, NULL, &r);
    SDL_RenderPresent(gRenderer);

    waitUntilKeyPressed();

    SDL_DestroyTexture(endScreenTexture);
    endScreenTexture = NULL;

    clearGame();
}

void Game::clearGame() {
    quit = false;
    readyForUpdate = false;
    dragging = false;
    callingEnemy = false;
    win = false;
    pause = false;
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
    for (int i = 0; i < guns.size(); i++) {
        delete guns[i];
        guns[i] = NULL;
    }
    guns.clear();
    for (int i = 0; i < supporters.size(); i++) {
        delete supporters[i];
        supporters[i] = NULL;
    }
    supporters.clear();
}

void Game::quitGame() {
    delete sound;
    delete menu;
    sound = NULL;
    menu = NULL;
    quitSDL(gWindow, gRenderer);
}
