#include "gun.h"

Gun::Gun(SDL_Renderer* &gRenderer, double x, double y, int _type) {
    // load gun texture
    gTexture = loadTexture(gRenderer, GUN_PATH[_type]);
    // use the first value array
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
    dstrect_g.x = gX - GUN_SIZE/2; dstrect_g.y = gY - GUN_SIZE/2;
    dstrect_g.h = GUN_SIZE; dstrect_g.w = GUN_SIZE;

    // load range shooting circle texture
    cTexture = loadTexture(gRenderer, SHOOTING_RANGE_CIRCLE_PATH);
    // circle position follow the gun position
    setRange(G_RANGE[_type]);
    // make the circle is transparent
    SDL_SetTextureBlendMode(cTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(cTexture, 30);

    // load update board texture
    ubTexture = loadTexture(gRenderer, UPDATE_BOARD_PATH);
    dstrect_ub.h = UPDATE_BOARD_HEIGHT;
    dstrect_ub.w = UPDATE_BOARD_WIDTH;
    dstrect_ub.x = PLAY_ZONE_X/2 - UPDATE_BOARD_WIDTH/2;
    dstrect_ub.y = 374;

    // inc button
    ibTexture = loadTexture(gRenderer, INC_BUTTON_PATH);
    dstrect_ib[0].h = 30; dstrect_ib[0].w = 30; dstrect_ib[0].x = 0; dstrect_ib[0].y = 0;
    dstrect_ib[1].h = 30; dstrect_ib[1].w = 30; dstrect_ib[1].x = 0; dstrect_ib[1].y = 65;
    dstrect_ib[2].h = 30; dstrect_ib[2].w = 30; dstrect_ib[2].x = 0; dstrect_ib[2].y = 130;
    
    // lever
    lTexture = loadTexture(gRenderer, LEVER_PATH);
    dstrect_l[0].h = 35; dstrect_l[0].w = 75; dstrect_l[0].x = 0; dstrect_l[0].y = 30;
    dstrect_l[1].h = 35; dstrect_l[1].w = 75; dstrect_l[1].x = 0; dstrect_l[1].y = 95;
    dstrect_l[2].h = 35; dstrect_l[2].w = 75; dstrect_l[2].x = 0; dstrect_l[2].y = 160;

    // block
    bTexture = loadTexture(gRenderer, BLOCK_PATH);
    dstrect_b[0].h = 35; dstrect_b[0].w = 60; dstrect_b[0].x = 15; dstrect_b[0].y = 30;
    dstrect_b[1].h = 35; dstrect_b[1].w = 60; dstrect_b[1].x = 15; dstrect_b[1].y = 95;
    dstrect_b[2].h = 35; dstrect_b[2].w = 60; dstrect_b[2].x = 15; dstrect_b[2].y = 160;

    // true when click on gun
    showUpdate = false;
}
Gun::~Gun() {
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
}

void Gun::drawToRender(SDL_Renderer* &gRenderer) {
    SDL_RenderCopy(gRenderer, gTexture, NULL, &dstrect_g);
    // draw range shooting circle follow the gun when true
    if (showUpdate) {
        // shooting range circle
        SDL_RenderCopy(gRenderer, cTexture, NULL, &dstrect_c);
        // update board
        SDL_RenderCopy(gRenderer, ubTexture, NULL, &dstrect_ub);
        // update button
        for (int i = 0; i < 3; i++) {
            // inc button
            SDL_RenderCopy(gRenderer, ibTexture, NULL, &dstrect_ib[i]);
            // lever
            SDL_RenderCopy(gRenderer, lTexture, NULL, &dstrect_l[i]);
            // block
            SDL_RenderCopy(gRenderer, bTexture, NULL, &dstrect_b[i]);
        }
    }
}


bool Gun::clickOn() {
    if (showUpdate) {
        showUpdate = false;
        return false;
    } else {
        showUpdate = true;
        printf(" %d\n", damage);
        return true;
    }
}

int Gun::checkClickOnUpdateButton(int x, int y, int gem) {
    if (x >= dstrect_ib[0].x && x < dstrect_ib[0].x + 30 && y >= dstrect_ib[0].y && y < dstrect_ib[0].y + 30
        && d_lever < 4 && gem >= G_UPDATE_PRICE[type][d_lever]) {
            
        d_lever += 1;
        damage += G_INC_DAMAGE[type][d_lever - 1];

        dstrect_b[0].w -= 15;
        dstrect_b[0].x += 15;

        return G_UPDATE_PRICE[type][d_lever - 1];
    }

    if (x >= dstrect_ib[1].x && x < dstrect_ib[1].x + 30 && y >= dstrect_ib[1].y && y < dstrect_ib[1].y + 30
        && s_lever < 4 && gem >= G_UPDATE_PRICE[type][s_lever]) {
        if (shotDelayTime - G_DEC_SHOT_DELAY_TIME[type] >= 0) {
            s_lever += 1;
        
            shotDelayTime -= G_DEC_SHOT_DELAY_TIME[type];

            dstrect_b[1].w -= 15;
            dstrect_b[1].x += 15;

            return G_UPDATE_PRICE[type][s_lever - 1];
        }  
    }

    if (x >= dstrect_ib[2].x && x < dstrect_ib[2].x + 30 && y >= dstrect_ib[2].y && y < dstrect_ib[2].y + 30
        && r_lever < 4 && gem >= G_UPDATE_PRICE[type][r_lever]) {
            
        r_lever += 1;
        setRange(range + G_INC_RANGE[type]);

        dstrect_b[2].w -= 15;
        dstrect_b[2].x += 15;

        return G_UPDATE_PRICE[type][s_lever - 1];
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

void Gun::setTimeID() {timeID = SDL_GetTicks();}
Uint32 Gun::getTimeID() {return timeID;}
int Gun::getShotDelayTime() {return shotDelayTime;}

void Gun::unShowUpdate() {showUpdate = false;}

double Gun::getX() {return gX;}
double Gun::getY() {return gY;}

bool Gun::onShot(double x, double y) {
    if (sqrt((gX - x)*(gX - x) + (gY - y)*(gY - y)) <= range)
        return true;
    else return false;
}


