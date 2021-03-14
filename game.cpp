#include "game.h"

void Game::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError("SDL_Init", true);

    gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (gWindow== nullptr)
        logSDLError("CreateWindow", true);

    gRenderer= SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (gRenderer == nullptr)
        logSDLError("CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::quitSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    IMG_Quit();
}

void Game::logSDLError(const std::string &msg, bool fatal) {
    std::cout << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void Game::drawBackground(SDL_Texture* &bgTexture) {
    SDL_RenderCopy(gRenderer, bgTexture, NULL, NULL);
}

void Game::drawPauseButton() {
    SDL_Rect dstrect;
    dstrect.x = 890; dstrect.y = 10;
    dstrect.h = 50; dstrect.w = 50;
    SDL_RenderCopy(gRenderer, psTexture, NULL, &dstrect);
}

void Game::drawLaze(double pX, double pY, double mX, double mY) {
    SDL_RenderDrawLine(gRenderer, pX, pY,
                                (mX - pX) * PLAY_ZONE_DIAGONAL / sqrt((mX-pX)*(mX-pX) + (mY-pY)*(mY-pY)) + pX,
                                (mY - pY) * PLAY_ZONE_DIAGONAL / sqrt((mX-pX)*(mX-pX) + (mY-pY)*(mY-pY)) + pY);
}

void Game::addThreat() {
    threatsSize++;
    int x = rand() % PLAY_ZONE_W + PLAY_ZONE_X;
    int y = rand() % PLAY_ZONE_H + PLAY_ZONE_Y;
    pthreat = new Threat(gRenderer, x, y);
    threats.push_back(pthreat);
    pthreat = NULL;
}

void Game::drawThreatList() {
    for (int i = 0; i < threatsSize; i++) {
        threats[i]->drawThreat(gRenderer);
    }
}

void Game::addBullet(double pX, double pY, double mX, double mY) {
    bulletsSize++;
    pBullet = new Bullet(gRenderer);
    pBullet->setFirstX(pX);
    pBullet->setFirstY(pY);
    pBullet->setX((mX - pX) * (PLAYER_SIZE/2 + BULLET_SIZE/2) / sqrt((mX - pX)*(mX - pX) + (mY - pY)*(mY - pY)) + pX);
    pBullet->setY((mY - pY) * (PLAYER_SIZE/2 + BULLET_SIZE/2) / sqrt((mX - pX)*(mX - pX) + (mY - pY)*(mY - pY)) + pY);
    pBullet->setDistance(PLAYER_SIZE/2 + BULLET_SIZE/2);
    bullets.push_back(pBullet);
    pBullet = NULL;
}

void Game::drawBulletList() {
    for (int i = 0; i < bulletsSize; i++) {
        bullets[i]->drawBullet(gRenderer);
        bullets[i]->updatePos();
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

void Game::handleCollision() {
    for (int i = bulletsSize-1; i >= 0; i--) {
        for (int j = threatsSize-1; j >= 0; j--) {
            if (sqrt((bullets[i]->getX() - threats[j]->getX())*(bullets[i]->getX() - threats[j]->getX()) + (bullets[i]->getY() - threats[j]->getY())*(bullets[i]->getY() - threats[j]->getY())) < PLAYER_SIZE/2 + BULLET_SIZE/2) {
                delete bullets[i];
                delete threats[j];
                bullets.erase(bullets.begin() + i);    
                threats.erase(threats.begin() + j);
            }
        }
    }
    bulletsSize = bullets.size();
    threatsSize = threats.size();
}

void Game::getKeyMove(SDL_Event &e, bool &u, bool &r, bool &d, bool &l) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: u = true;
                break;
            case SDLK_RIGHT: r = true;
                break;
            case SDLK_DOWN: d = true;
                break;
            case SDLK_LEFT: l = true;
                break;
        }
    }
    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: u = false;
                break;
            case SDLK_RIGHT: r = false;
                break;
            case SDLK_DOWN: d = false;
                break;
            case SDLK_LEFT: l = false;
                break;
        }
    }
}

void Game::start() {
    initSDL();

    // event
    SDL_Event e;

    menu = new Menu(gRenderer);
    menu->drawMenu(gRenderer);
    SDL_RenderPresent(gRenderer);

    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                switch (menu->clickOn(x, y)) {
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
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    srand(time(0));
    // background texture
    bgTexture1 = loadTexture(gRenderer, BACKGROUND1);
    bgTexture2 = loadTexture(gRenderer, BACKGROUND2);
    // pause button
    psTexture = loadTexture(gRenderer, PAUSE);
}

void Game::play() {
    setUp();

    // event
    SDL_Event e;

    
    // new player
    player = new Player(gRenderer);

    // threat list

    // mouse position
    double mouseX, mouseY;

    // key move
    bool keyUpPressed = false, keyRightPressed = false, keyDownPressed = false, keyLeftPressed = false;

    while (true) {
        // read event
        while (SDL_PollEvent(&e)) {

            // get mouse position
            if (e.motion.x >= 0 && e.motion.x <= SCREEN_WIDTH) mouseX = e.motion.x;
            if (e.motion.y >= 0 && e.motion.y <= SCREEN_HEIGHT) mouseY = e.motion.y;
            
            // get click event
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                addBullet(player->getX(), player->getY(), mouseX, mouseY);
            }

            // get key event for move
            getKeyMove(e, keyUpPressed, keyRightPressed, keyDownPressed, keyLeftPressed);

        }

        // set player position
        if (keyLeftPressed) player->setX(player->getX() - STEP);
        if (keyRightPressed) player->setX(player->getX() + STEP);
        if (keyUpPressed) player->setY(player->getY() - STEP);
        if (keyDownPressed) player->setY(player->getY() + STEP);

        drawBackground(bgTexture1);

        player->drawPlayer(gRenderer);

        drawLaze(player->getX(), player->getY(), mouseX, mouseY);

        if (threatsSize == 0) addThreat();

        drawThreatList();

        drawBulletList();        

        handleCollision();

        removeBulletOutScreen();

        drawBackground(bgTexture2);

        drawPauseButton();

        SDL_RenderPresent(gRenderer);

    }
}

void Game::quitGame() {
    delete menu;
    delete player;
    delete pthreat;
    delete pBullet;
    menu = NULL;
    player = NULL;
    pthreat = NULL;
    pBullet = NULL;
    threats.clear();
    bullets.clear();
    SDL_DestroyTexture(bgTexture1);
    SDL_DestroyTexture(bgTexture2);
    quitSDL();
    printf("quit\n");
}