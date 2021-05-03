#include "game.h"

void Game::start() {
    initSDL(gWindow, gRenderer);

    gTexture = new gameTexture(gRenderer);

    menu = new Menu();
    sound = new Sound();
    sound->playMusic();

    while (true) {
        menu->drawMenu(gRenderer, gTexture);
        SDL_RenderPresent(gRenderer);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                SDL_GetMouseState(&clickX, &clickY);
                switch (menu->clickOn(clickX, clickY)) {
                    case 1:
                        if (quit_and_resume) clearGame();
                        setUp();
                        play();
                        sound->playClickSound();
                        break;
                    case 2:
                        setUpGameForResume();
                        play();
                        sound->playClickSound();
                        break;
                    case 3:
                        menu->optionsMenu(gRenderer, gTexture, sound);
                        break;
                    case 4:
                        quitGame();
                        sound->playClickSound();
                        return;
                }
            }
        }
    }
}

void Game::setUp() {
    ctb = new ctBoard();

    map = new Map();
    map->readFromFile(quit);
    for (int i = 0; i < MAP_SIZE; i++) mapOfObject[i] = -2;
    map->buildMapOfObject(mapOfObject);

    base = new Base(map->getYLast());

    readWaveData();

    timeWriter = new Writer("fonts/comicbd.ttf", 20, 243, 156, 18);
    waveWriter = new Writer("fonts/ALGER.ttf", 25, 0, 0, 0);

    for (int i = 0; i < MAP_SIZE; i++) {gunObject[i] = NULL; supporterObject[i] = NULL;}

    curWave = 0; noticeWave = 0;

    waitTimeTransWave = WAITING_WAVE_TIME_DEFAULT;
    waitTimeCallEnemy = 700;

    callingEnemy = false;
    callNextWave = false;

    win = false;
    quit = false;
    quit_and_resume = false;

}

void Game::play() {

    while (!quit) {
        if (curWave == wave.size() && enemys.size() == 0) {
                win = true;
                break;
        }

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

                if (ctb->clickPauseButton(clickX, clickY)) {
                    ctb->pauseMenu(gRenderer, gTexture, sound, quit_and_resume);
                    if (quit_and_resume) {
                        menu->setDstRectButton(true);
                        return;
                    }
                    timeID += ctb->getTimePause();
                }

                if (ctb->clickNextButton(clickX, clickY)) {
                    if (curWave != wave.size() && !wave[curWave].started) {
                        callNextWave = true;
                        waitTimeTransWave = 0;
                    }
                }

                if (ctb->aTowerIsChosen(clickX, clickY)) {
                    dragging = true;
                    resetUpdateDisplay(NULL, NULL);
                }

                treatPosition(clickX, clickY, row, col);
                if (row > -1 && col > -1) {
                    if (gunObject[row * 15 + col] != nullptr) {
                        if (gunObject[row * 15 + col]->clickOn()) {
                            resetUpdateDisplay(gunObject[row * 15 + col], NULL);
                            readyForUpdate = true;
                            indexOfObject = row * 15 + col;
                        } else {
                            readyForUpdate = false;
                        }
                    } else if (supporterObject[row * 15 + col] != nullptr) {
                        if (supporterObject[row * 15 + col]->clickOn())
                            resetUpdateDisplay(NULL, supporterObject[row * 15 + col]);
                    } else resetUpdateDisplay(NULL, NULL);
                }

                if (readyForUpdate) {
                    if (gunObject[indexOfObject] != nullptr)
                        ctb->setGem(-(gunObject[indexOfObject]->checkClickOnUpdateButton(clickX, clickY, ctb->getGem())));
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

                            readyForUpdate = true;
                            indexOfObject = row * 15 + col;
                        }
                    }
                }
            }
        }

        if ((enemys.size() == 0 || callNextWave) && !wave[curWave].started) waitingForNextWave();

        if (wave[curWave].started) callEnemy();

        sortEnemyList();

        freeFire();

        renderCurrent();

        if (base->destroyed()) {
            win = false;
            break;
        }
        noticeWaveCurrent();

        treatWhenEnemyGetHit();
        remoteEnemyDied();
        removeBulletOutScreen();
        removeEnemyFinished();

        SDL_RenderPresent(gRenderer);

    }

    endGame();
}

void Game::endGame() {

    SDL_Texture* endScreenTexture = NULL;
    if (win) {
        loadTexture(gRenderer, endScreenTexture, "images/win.png");
    } else {
        loadTexture(gRenderer, endScreenTexture, "images/lose.png");
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
    menu->setDstRectButton(false);
}

void Game::clearGame() {
    quit = false;
    readyForUpdate = false;
    dragging = false;
    callingEnemy = false;
    callNextWave = false;
    win = false;
    quit = false;
    delete ctb;
    delete map;
    delete base;
    delete timeWriter;
    delete waveWriter;
    ctb = NULL;
    map = NULL;
    base = NULL;
    timeWriter = NULL;
    waveWriter = NULL;
    for (int i = 0; i < guns.size(); i++) {
        delete guns[i];
        guns[i] = NULL;
    }
    for (int i = 0; i < supporters.size(); i++) {
        delete supporters[i];
        supporters[i] = NULL;
    }
    for (int i = 0; i < enemys.size(); i++) {
        delete enemys[i];
        enemys[i] = NULL;
    }
    for (int i = 0; i < bullets.size(); i++) {
        delete bullets[i];
        bullets[i] = NULL;
    }
    wave.clear();
    enemys.clear();
    bullets.clear();
    guns.clear();
    supporters.clear();
}

void Game::quitGame() {
    delete gTexture;
    delete sound;
    delete menu;
    gTexture = NULL;
    sound = NULL;
    menu = NULL;
    quitSDL(gWindow, gRenderer);
}

void Game::readWaveData() {
    ifstream finp("wave/map1.in");
    if (finp.fail()) {printf(" -failed to open wave.in\n"); quit = true; return;}
    int n_wave;
    finp >> n_wave;
    for (int i = 0; i < n_wave; i++) {
        Wave re;
        finp >> re.amountOfType;
        for (int j = 0; j < re.amountOfType; j++) {
            int a, b;
            finp >> a >> b;
            re.enemyType.push_back(a);
            re.amountOfEnemy.push_back(b);
        }
        wave.push_back(re);
    }
    finp.close();
}

void Game::setUpGameForResume() {
    for (int i = 0; i < enemys.size(); i++) delete enemys[i];
    enemys.clear();

    for (int i = 0; i < bullets.size(); i++) delete bullets[i];
    bullets.clear();

    wave[noticeWave-1].setUpForResume();

    noticeWave = curWave;

    quit_and_resume = false;
}

void Game::addGun(double x, double y, int type) {
    treatPosition(x, y, row, col);
    if (gunObject[row * 15 + col] != nullptr) return;
    gunObject[row * 15 + col] = new Gun(x, y, type);
    guns.push_back(gunObject[row * 15 + col]);

    gunGetBuff(guns[guns.size()-1]);
}

void Game::addSupporter(double x, double y, int type) {
    treatPosition(x, y, row, col);
    if (supporterObject[row * 15 + col] != nullptr) return;
    supporterObject[row * 15 + col] = new Supporter(x, y, type);
    supporters.push_back(supporterObject[row * 15 + col]);

    buffForGun(supporters[supporters.size()-1]);
}

void Game::addBullet(double gX, double gY, Enemy* &_enemy, int dmg, int type) {
    bullets.push_back(new Bullet(gX, gY, _enemy, dmg, type));
}

void Game::buffForGun(Supporter* &pSupporter) {
    for (int i = 0; i < guns.size(); i++)
        if (pSupporter->inRange(guns[i]->getX(), guns[i]->getY())) guns[i]->setBuff(pSupporter->getType(), pSupporter->getBuff());
}

void Game::gunGetBuff(Gun* &pGun) {
    for (int i = 0; i < supporters.size(); i++)
        if (supporters[i]->inRange(pGun->getX(), pGun->getY())) pGun->setBuff(supporters[i]->getType(), supporters[i]->getBuff());
}

void Game::waitingForNextWave() {
    if (wave[curWave].timeStarted == false) {
        noticeWave++;
        wave[curWave].timeStarted = true;
        timeID = SDL_GetTicks();
        return;
    } else {
        if (SDL_GetTicks() - timeID >= waitTimeTransWave) {
            wave[curWave].started = true;
        }
    }

    waitTimeTransWave = WAITING_WAVE_TIME_DEFAULT;
    callNextWave = false;
}

void Game::callEnemy() {
    if (wave[curWave].nextWave) {
        curWave++; return;
    }
    if (callingEnemy == false) {
        callingEnemy = true;
        timeID = SDL_GetTicks();
        return;
    } else {
        if (SDL_GetTicks() - timeID >= waitTimeCallEnemy) {
            enemys.push_back(new Enemy(map->getYFirst()*50+25 + PLAY_ZONE_Y, wave[curWave].nextEnemy()));
            timeID = SDL_GetTicks();
        }
    }
}

void Game::sortEnemyList() {
    int e_n = enemys.size();
    for (int i = 0; i < e_n-1; i++) {
        for (int j = i+1; j < e_n; j++) {
            if (i == j) break;
            int iPos = enemys[i]->getCurrentPos();
            int jPos = enemys[j]->getCurrentPos();
            if (iPos < jPos) eSwap(enemys[i], enemys[j]);
            else if (iPos == jPos) {
                int d = map->getDir(iPos);
                switch (d) {
                    case 0:
                        if (enemys[i]->getY() > enemys[j]->getY()) eSwap(enemys[i], enemys[j]);
                        break;
                    case 1:
                        if (enemys[i]->getX() < enemys[j]->getX()) eSwap(enemys[i], enemys[j]);
                        break;
                    case 2:
                        if (enemys[i]->getY() < enemys[j]->getY()) eSwap(enemys[i], enemys[j]);
                        break;
                    case 3:
                        if (enemys[i]->getX() > enemys[j]->getX()) eSwap(enemys[i], enemys[j]);
                        break;
                }
            }
        }
    }
}

void Game::eSwap(Enemy* &e1, Enemy* &e2) {
    Enemy* e = e1; e1 = e2; e2 = e;
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
                    guns[i]->fire(sound);
                }
                break;
            }
        }
    }
}

void Game::treatWhenEnemyGetHit() {
    for (int i = bullets.size()-1; i >= 0; i--) {
        for (int j = enemys.size()-1; j >= 0; j--) {
            // rocket not boom if doesn't meet target
            if (bullets[i]->getType() == 3 && bullets[i]->getTarget() != enemys[j]) {
                if (j == 0) {
                    //bullets[i]->targetKilled();
                    bullets[i]->findNewTarget(enemys);
                }
                continue;
            }

            if ((bullets[i]->getType() == 2 && enemys[j]->getHit(bullets[i]->getLastX(), bullets[i]->getLastY(), bullets[i]->getDamage(), bullets[i]->getType()))
                || (bullets[i]->getType() != 2 && enemys[j]->getHit(bullets[i]->getX(), bullets[i]->getY(), bullets[i]->getDamage(), bullets[i]->getType()))) {

                if (bullets[i]->getType() == 3) treatWhenRocketBoom(bullets[i]);
                //if (enemys[j]->isDead()) bullets[i]->targetKilled();
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                break;
            }
        }

    }
}

void Game::treatWhenRocketBoom(Bullet* &rocket) {
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

void Game::removeEnemyFinished() {
    for (int i = enemys.size()-1; i >= 0; i--) {
        if (enemys[i]->isSuccess()) {
            base->setHP(enemys[i]->getDamage());
            base->drawGettingHitEffect(gRenderer, gTexture);
            sound->playEffectSoundWhenGetHurt();
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

void Game::resetUpdateDisplay(Gun* const &pGun, Supporter* const &pSupporter) {
    for (int i = 0; i < guns.size(); i++)
        if (guns[i] != pGun) guns[i]->unenableUpdate();
    for (int i = 0; i < supporters.size(); i++)
        if (supporters[i] != pSupporter) supporters[i]->unenableUpdate();
}

void Game::renderCurrent() {
    drawMap();
    drawBase();

    drawEnemy();
    drawGun();
    drawSupporter();
    drawRange();
    drawBullets();

    drawControlBoard();
    drawUpdateBoard();

    if (dragging) {
        if (ctb->getGemOfItemChosen() <= ctb->getGem()) {
            ctb->drawTowerChosen(gRenderer, gTexture, e.motion.x, e.motion.y);
        }
    } else {
        ctb->drawReviewBoard(gRenderer, gTexture, e.motion.x, e.motion.y);
    }

    showWaitTime();
}

void Game::drawMap() {
    map->drawToRender(gRenderer, gTexture);
}

void Game::drawControlBoard() {
    ctb->drawToRender(gRenderer, gTexture, base->getHPRate());

    if (curWave != wave.size() && !wave[curWave].started)
        ctb->drawNextButton(gRenderer, gTexture, 1);
    else ctb->drawNextButton(gRenderer, gTexture, 0);
}

void Game::drawBase() {
    base->drawToRender(gRenderer, gTexture);
}

void Game::drawEnemy() {
    for (int i = 0; i < enemys.size(); i++) {
        enemys[i]->drawToRender(gRenderer, gTexture);
        enemys[i]->updatePos(map->getDir(), map->getXRoad(), map->getYRoad());
    }
}

void Game::drawGun() {
    for (int i = 0; i < guns.size(); i++) {
        guns[i]->drawToRender(gRenderer, gTexture);
    }
}

void Game::drawSupporter() {
    for (int i = 0; i < supporters.size(); i++) {
        supporters[i]->drawToRenderer(gRenderer, gTexture);
    }
}

void Game::drawRange() {
    for (int i = 0; i < guns.size(); i++) {
        guns[i]->drawRangeCircle(gRenderer, gTexture);
    }
    for (int i = 0; i < supporters.size(); i++) {
        supporters[i]->drawRangeCircle(gRenderer, gTexture);
    }
}

void Game::drawBullets() {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->drawToRender(gRenderer, gTexture);
    }
}

void Game::drawUpdateBoard() {
    for (int i = 0; i < guns.size(); i++) {
        guns[i]->drawUpdateBoard(gRenderer, gTexture, ctb->getGem());
    }
}

void Game::noticeWaveCurrent() {
    waveWriter->writeText(gRenderer, "Wave " + to_string(noticeWave) + "/" + to_string(wave.size()), 10, 93);
}

void Game::showWaitTime() {
    if (enemys.size() == 0 && !wave[curWave].started) {
        int remainingTime;

        if (waitTimeTransWave == 0) remainingTime = 0;
        else remainingTime = waitTimeTransWave - SDL_GetTicks() + timeID;

        if (remainingTime / 1000 > 3) timeWriter->setColorText(0, 0, 0);
        else timeWriter->setColorText(255, 0, 0);

        if ((remainingTime >= 3500)
            || (remainingTime < 3000 && remainingTime >= 2500)
            || (remainingTime < 2000 && remainingTime >= 1750)
            || (remainingTime < 1500 && remainingTime >= 1250)
            || (remainingTime < 1000 && remainingTime >= 750)
            || (remainingTime < 500 && remainingTime >= 250))
        timeWriter->writeText(gRenderer, "Next wave in: " + to_string(remainingTime / 1000) + "s", 100, 4);
    }
}
