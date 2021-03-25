#include "game.h"

void Game::drawMap() {
    SDL_RenderCopy(gRenderer, mapTexture, NULL, NULL);
}

void Game::drawControlBoard() {
    ctb->drawToRender(gRenderer);
}

void Game::drawEnemy() {
    for (int i = 0; i < enemys.size(); i++) {
        enemys[i]->drawToRender(gRenderer);
        enemys[i]->updatePos();
    }
}

void Game::drawGun() {
    for (int i = 0; i < guns.size(); i++) {
        guns[i]->drawToRender(gRenderer);
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

        // add enemy
        enemys.push_back(new Enemy(gRenderer, 0, PLAY_ZONE_Y + PLAY_ZONE_H/2,wave[curWave].nextEnemy()));
        return;
    } else {
        if (SDL_GetTicks() - timeID >= waitTimeCallEnemy) {
            enemys.push_back(new Enemy(gRenderer, 0, PLAY_ZONE_Y + PLAY_ZONE_H/2,wave[curWave].nextEnemy()));
            timeID = SDL_GetTicks();
        }
    }

}

void Game::addGun(double x, double y, int type) {
    guns.push_back(new Gun(gRenderer, x, y, type));
}

void Game::addEnemy() {
    enemys.push_back(new Enemy(gRenderer, 0, PLAY_ZONE_Y + PLAY_ZONE_H/2, 0));
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
    for (int i = 0; i < guns.size(); i++) {
        for (int j = 0; j < enemys.size(); j++) {
            if (enemys[j]->getX() + ENEMY_SIZE/2 >= PLAY_ZONE_X)
            if (guns[i]->onShot(enemys[j]->getX(), enemys[j]->getY())) {
                addBullet(guns[i]->getX(), guns[i]->getY(), enemys[j]->getX(), enemys[j]->getY(), guns[i]->getDamage());
                break;
            }
        }
    }
}

void Game::treatWhenEnemyGetHit() {
    for (int i = bullets.size()-1; i >= 0; i--) {
        for (int j = enemys.size()-1; j >= 0; j--) {
            if (enemys[j]->getHit(bullets[i]->getX(), bullets[i]->getY(), bullets[i]->getDamage())) {
                if (enemys[j]->isDead()) {
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
            delete enemys[i];
            enemys.erase(enemys.begin() + i);
        }
    }
}

void Game::start() {
    initSDL(gWindow, gRenderer);

    menu = new Menu(gRenderer);

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
                        menu->option();
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
    // load background texture
    mapTexture = loadTexture(gRenderer, MAP);

    ctb = new ctBoard(gRenderer);

    // read enemy wave data
    if (!readWaveData(wave)) {
        quit = true;
        return;
    }

    curWave = 0;
    callingEnemy = false;
    quit = false;
}

void Game::renderCurrent() {
    drawMap();
    drawControlBoard();

    noticeWaveCurrent();

    drawEnemy();
    drawGun();
    drawBullets();

    // render if grag a gun for attack
    if (mouseDown) {
        if (ctb->aGunItemChosen(clickX, clickY)) {
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
            }
            if (dragging)
                if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = false;
                    dragging = false;
                    addGun(mouseX, mouseY, ctb->getTypeOfGunChosen());
                }

        }

        if (curWave == wave.size()) break;
        else {
        if (wave[curWave].started == false) waitingForNextWave();
        if (wave[curWave].started == true) callEnemy();
        }

        freeFire();

        treatWhenEnemyGetHit();

        remoteEnemyDied();
        removeBulletOutScreen();
        removeEnemyFinished();

        renderCurrent();

        SDL_RenderPresent(gRenderer);

    }

    endGame();
}

void Game::endGame() {
    clearGame();
    printf("done\n");
}

void Game::clearGame() {
    quit = false;
    delete ctb;
    ctb = NULL;
    wave.clear();
    guns.clear();
    bullets.clear();
}

void Game::quitGame() {
    clearGame();
    delete menu;
    menu = NULL;
    SDL_DestroyTexture(mapTexture);
    quitSDL(gWindow, gRenderer);
    printf("quit\n");
}