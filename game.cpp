#include "game.h"

void Game::drawMap() {
    SDL_RenderCopy(gRenderer, mapTexture, NULL, NULL);
}

void Game::drawControlBoard() {
    ctb->drawToRender(gRenderer);
}

void Game::drawEnemy() {
    for (int i = 0; i < enemysSize; i++) {
        enemys[i]->drawToRender(gRenderer);
        enemys[i]->updatePos();
    }
}

void Game::drawGun() {
    for (int i = 0; i < gunsSize; i++) {
        guns[i]->drawToRender(gRenderer);
    }
}

void Game::drawBullets() {
    for (int i = 0; i < bulletsSize; i++) {
        bullets[i]->drawToRender(gRenderer);
        bullets[i]->updatePos(0);
    }
}

void Game::addGun(double x, double y, int type) {
    gunsSize++;
    guns.push_back(new Gun(gRenderer, x, y, type));
}

void Game::addEnemy() {
    enemysSize++;
    enemys.push_back(new Enemy(gRenderer, 0, PLAY_ZONE_Y + PLAY_ZONE_H/2, 0));
}

void Game::freeFire() {
    for (int i = 0; i < gunsSize; i++) {
        for ()
    }
}

void Game::removeBulletOutScreen() {
    for (int i = bulletsSize-1; i >= 0; i--) {
        if (bullets[i]->outOfScreen()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
    bulletsSize = bullets.size();
}

void Game::removeEnemyFinished() {
    while (enemys[0]->isSuccess()) {
        enemys.erase(enemys.begin());
    }
    enemysSize = enemys.size();
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
                        break;
                }
            }
        }
    }    
}

void Game::setUp() {
    srand(time(0));
    // background texture
    mapTexture = loadTexture(gRenderer, MAP);

    ctb = new ctBoard(gRenderer);

    gunsSize = 0;
    enemysSize = 0;
    bulletsSize = 0;
    quit = false;
}

void Game::renderCurrent() {
    drawMap();
    drawControlBoard();
    drawEnemy();
    drawGun();
    drawBullets();
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

        addEnemy();
        printf("%d\n",gunsSize);

        removeBulletOutScreen();
        removeEnemyFinished();

        renderCurrent();

        // render if grag a gun for attack
        if (mouseDown) {
            if (ctb->aGunItemChosen(clickX, clickY)) {
                ctb->drawGunChosen(gRenderer, e.motion.x, e.motion.y);
                dragging = true;
            }
        }

        SDL_RenderPresent(gRenderer);

    }

    endGame();
}

void Game::endGame() {
    clearGame();
    
}

void Game::clearGame() {
    quit = false;
    delete ctb;
    ctb = NULL;
    guns.clear();
    bullets.clear();
    gunsSize = 0;
    bulletsSize = 0;
}

void Game::quitGame() {
    clearGame();
    delete menu;
    menu = NULL;
    SDL_DestroyTexture(mapTexture);
    quitSDL(gWindow, gRenderer);
    printf("quit\n");
}

// bulletsSize++;
    // pBullet = new Bullet(gRenderer);

    // pBullet->setFirstX(player->getX());
    // pBullet->setFirstY(player->getY());

    // double d = sqrt((mouseX - player->getX())*(mouseX - player->getX()) + (mouseY - player->getY())*(mouseY - player->getY()));
    // pBullet->setX((mouseX - player->getX()) * (GUN_SIZE/2 + BULLET_SIZE/2) / d + player->getX());
    // pBullet->setY((mouseY - player->getY()) * (GUN_SIZE/2 + BULLET_SIZE/2) / d + player->getY());

    // pBullet->setDistance(GUN_SIZE/2 + BULLET_SIZE/2);

    // bullets.push_back(pBullet);
    // pBullet = NULL;
    