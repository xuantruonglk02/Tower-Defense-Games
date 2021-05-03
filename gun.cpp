#include "gun.h"

Gun::Gun(double x, double y, int _type) {

    type = _type;

    damage = G_DAMAGE[_type];
    d_lever = 0;

    // set up delay time
    shotDelayTime = G_SHOT_DELAY_TIME[_type];
    s_lever = 0;
    // start time counter
    timeID = SDL_GetTicks();

    range = G_RANGE[_type];
    r_lever = 0;
    
    price = G_PRICE[_type];
    
    // gun position
    gX = (int)(x / 50) * 50 + 25;
    gY = (int)(y / 50) * 50 + 25;

    dstrect_g[0].h = GUN_H[type][0]; dstrect_g[0].w = GUN_W[type][0];
    dstrect_g[0].x = gX - dstrect_g[0].w / 2; dstrect_g[0].y = gY - dstrect_g[0].h / 2;
    centerPoint_g[0] = {dstrect_g[0].w / 2, dstrect_g[0].h / 2};

    dstrect_g[1].h = GUN_H[type][1]; dstrect_g[1].w = GUN_W[type][1];
    dstrect_g[1].x = gX - dstrect_g[1].w / 2; dstrect_g[1].y = gY - dstrect_g[1].h / 2;
    centerPoint_g[1] = {dstrect_g[1].w / 2, dstrect_g[1].h / 2};

    dstrect_bs.h = GUN_BASE_SIZE; dstrect_bs.w = GUN_BASE_SIZE;
    dstrect_bs.x = gX - dstrect_bs.w / 2; dstrect_bs.y = gY - dstrect_bs.h / 2;

    degree = 0;

    if (_type == 3) {

        dstrest_rk.h = ROCKET_FIRST_H; dstrest_rk.w = ROCKET_FIRST_W;
        dstrest_rk.x = gX - dstrest_rk.w / 2;
        dstrest_rk.y = gY - dstrest_rk.h / 2;

        centerPoint_rk = {dstrest_rk.w / 2, dstrest_rk.h / 2};

        showRocket = true;
    }

    // circle position follow the gun position
    setRange(G_RANGE[_type]);

    // load update board texture
    dstrect_ub.h = UPDATE_BOARD_H;
    dstrect_ub.w = UPDATE_BOARD_W;
    dstrect_ub.x = 3;
    dstrect_ub.y = PLAY_ZONE_Y + PLAY_ZONE_H - dstrect_ub.h;
    
    // lever
    dstrect_l[0].h = 35; dstrect_l[0].w = 75; dstrect_l[0].x = dstrect_ub.x + 5; dstrect_l[0].y = dstrect_ub.y + 5+5+15+7;
    dstrect_l[1].h = 35; dstrect_l[1].w = 75; dstrect_l[1].x = dstrect_l[0].x; dstrect_l[1].y = dstrect_l[0].y + 68;
    dstrect_l[2].h = 35; dstrect_l[2].w = 75; dstrect_l[2].x = dstrect_l[0].x; dstrect_l[2].y = dstrect_l[1].y + 68;

    // block
    dstrect_b[0].h = 35; dstrect_b[0].w = 60; dstrect_b[0].x = dstrect_l[0].x + 15; dstrect_b[0].y = dstrect_l[0].y;
    dstrect_b[1].h = 35; dstrect_b[1].w = 60; dstrect_b[1].x = dstrect_l[1].x + 15; dstrect_b[1].y = dstrect_l[1].y;
    dstrect_b[2].h = 35; dstrect_b[2].w = 60; dstrect_b[2].x = dstrect_l[2].x + 15; dstrect_b[2].y = dstrect_l[2].y;

    // inc button
    dstrect_ib[0].h = 30; dstrect_ib[0].w = 30; dstrect_ib[0].x = dstrect_ub.x + dstrect_l[0].w + 5+5; dstrect_ib[0].y = dstrect_ub.y + 5+5+15+10;
    dstrect_ib[1].h = 30; dstrect_ib[1].w = 30; dstrect_ib[1].x = dstrect_ib[0].x; dstrect_ib[1].y = dstrect_ib[0].y + 68;
    dstrect_ib[2].h = 30; dstrect_ib[2].w = 30; dstrect_ib[2].x = dstrect_ib[0].x; dstrect_ib[2].y = dstrect_ib[1].y + 68;

    // true when click on gun
    showUpdate = true;

    frame = 0;
}
Gun::~Gun() {}

void Gun::drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    // draw base
    SDL_RenderCopy(gRenderer, gTexture->baseGunTexture, NULL, &dstrect_bs);
    SDL_RenderCopyEx(gRenderer, gTexture->gunTexture[type][frame], NULL, &dstrect_g[frame], degree, &centerPoint_g[frame], SDL_FLIP_NONE);

    if (type == 3) {
        if (showRocket == false && SDL_GetTicks() - timeID >= G_SHOT_DELAY_TIME[type] / 3) showRocket = true;
        if (showRocket)
            SDL_RenderCopyEx(gRenderer, gTexture->rocketNotFireTexture, NULL, &dstrest_rk, degree, &centerPoint_rk, SDL_FLIP_NONE);
    }

    frame = 0;
}

void Gun::drawRangeCircle(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    // shooting range circle
    // draw range shooting circle follow the gun when true
    if (showUpdate)
        SDL_RenderCopy(gRenderer, gTexture->rangeCircleTexture, NULL, &dstrect_c);
}

void Gun::drawUpdateBoard(SDL_Renderer* &gRenderer, gameTexture* &gTexture, int gem) {
    // set update button display when enough money
    if (d_lever < 4 && gem >= G_UPDATE_PRICE[type][0][d_lever]) showUpdateButton[0] = true;
        else showUpdateButton[0] = false;
    if (s_lever < 4 && gem >= G_UPDATE_PRICE[type][1][s_lever]) showUpdateButton[1] = true;
        else showUpdateButton[1] = false;
    if (r_lever < 4 && gem >= G_UPDATE_PRICE[type][2][r_lever]) showUpdateButton[2] = true;
        else showUpdateButton[2] = false;
    // draw range shooting circle follow the gun when true
    if (showUpdate) {
        // update board
        SDL_RenderCopy(gRenderer, gTexture->updateBoardTexture, NULL, &dstrect_ub);
        // update button
        for (int i = 0; i < 3; i++) {
            // inc button
            if (showUpdateButton[i])
                SDL_RenderCopy(gRenderer, gTexture->updateButtonTexture, NULL, &dstrect_ib[i]);
            // lever
            SDL_RenderCopy(gRenderer, gTexture->leverTexture, NULL, &dstrect_l[i]);
            // block
            SDL_RenderCopy(gRenderer, gTexture->blockTexture, NULL, &dstrect_b[i]);
        }
    }
}

void Gun::changeShotDirection(int enemyX, int enemyY) {
    double r = sqrt((gX - enemyX)*(gX - enemyX) + (gY - enemyY)*(gY - enemyY));
    degree = asin((enemyX - gX) / r) * 180 / M_PI;
    if (enemyY > gY) degree = 180 - degree;
}

bool Gun::clickOn() {
    if (showUpdate) {
        showUpdate = false;
        return false;
    } else {
        showUpdate = true;
        return true;
    }
}

int Gun::checkClickOnUpdateButton(int x, int y, int gem) {
    if (x >= dstrect_ib[0].x && x < dstrect_ib[0].x + 30 && y >= dstrect_ib[0].y && y < dstrect_ib[0].y + 30 && showUpdateButton[0]) {
            
        d_lever += 1;
        damage += G_INC_DAMAGE[type][d_lever - 1];

        dstrect_b[0].w -= 15;
        dstrect_b[0].x += 15;

        return G_UPDATE_PRICE[type][0][d_lever - 1];
    }

    if (x >= dstrect_ib[1].x && x < dstrect_ib[1].x + 30 && y >= dstrect_ib[1].y && y < dstrect_ib[1].y + 30 && showUpdateButton[1]) {
        if (shotDelayTime - G_DEC_SHOT_DELAY_TIME[type][s_lever] >= 0) {
            s_lever += 1;
        
            shotDelayTime -= G_DEC_SHOT_DELAY_TIME[type][s_lever - 1];

            dstrect_b[1].w -= 15;
            dstrect_b[1].x += 15;

            return G_UPDATE_PRICE[type][1][s_lever - 1];
        }  
    }

    if (x >= dstrect_ib[2].x && x < dstrect_ib[2].x + 30 && y >= dstrect_ib[2].y && y < dstrect_ib[2].y + 30 && showUpdateButton[2]) {
            
        r_lever += 1;
        setRange(range + G_INC_RANGE[type][r_lever - 1]);

        dstrect_b[2].w -= 15;
        dstrect_b[2].x += 15;

        return G_UPDATE_PRICE[type][2][r_lever - 1];
    }

    return 0;
}

void Gun::setRange(int r) {
    range = r;
    dstrect_c.h = 2*r; dstrect_c.w = 2*r;
    dstrect_c.x = gX - dstrect_c.w / 2; dstrect_c.y = gY - dstrect_c.h / 2;
}

void Gun::setDamage(int k) {damage = k;}
int Gun::getDamage() {return damage;}

void Gun::setBuff(int typeOfSupporter, int buff) {
    if (typeOfSupporter == 0) damage += buff;
    else {
        range += buff;
        setRange(range);
    }
}

void Gun::setTimeID() {timeID = SDL_GetTicks();}
Uint32 Gun::getTimeID() {return timeID;}
int Gun::getShotDelayTime() {return shotDelayTime;}

void Gun::unenableUpdate() {showUpdate = false;}

int Gun::getType() {return type;}

int Gun::getX() {return gX;}
int Gun::getY() {return gY;}

void Gun::fire(Sound* sound) {
    frame++;
    showRocket = false;

    if (type < 2) sound->playGunShottingSound();
    else if (type == 2) sound->playLazeShottingSound();

}

bool Gun::onShot(double x, double y) {
    if (sqrt((gX - x)*(gX - x) + (gY - y)*(gY - y)) <= range) {
        return true;
    }
    else return false;
}


