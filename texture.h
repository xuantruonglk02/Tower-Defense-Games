#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "utils.h"

class gameTexture {
public:
    gameTexture(SDL_Renderer* &gRenderer) {
        // menu
        loadTexture(gRenderer, menuTexture, MENU_PATH);
        loadTexture(gRenderer, optionsMenuTexture, O_MENU_PATH);
        loadTexture(gRenderer, playButtonTexture, PLAY_PATH);
        loadTexture(gRenderer, resumeButtonTexture, RESUME_PATH);
        loadTexture(gRenderer, selectMapButtonTexture, SELECT_MAP_PATH);
        loadTexture(gRenderer, optionsButtonTexture, OPTIONS_PATH);
        loadTexture(gRenderer, quitButtonTexture, QUIT_PATH);
        loadTexture(gRenderer, muteTexture, MUTE_PATH);
        // control board
        loadTexture(gRenderer, controlBoardTexture, CTB_PATH);
        loadTexture(gRenderer, pauseButtonTexture, PAUSE_PATH);
        loadTexture(gRenderer, pauseMenuTexture, PAUSE_MENU_PATH);
        loadTexture(gRenderer, hpBarTexture, HPBAR_PATH);
        loadTexture(gRenderer, rangeCircleTexture, SHOOTING_RANGE_CIRCLE_PATH);
        loadTexture(gRenderer, lockGunTexture, LOCK_PATH);
        for (int i = 0; i < 2; i++) loadTexture(gRenderer, nextButtonTexture[i], NEXT_BUTTON_PATH[i]);
        for (int i = 0; i < 6; i++) {
            loadTexture(gRenderer, towerTexture[i], TOWER_PATH[i]);
            loadTexture(gRenderer, reviewBoardTexture[i], REVIEW_BOARD_PATH[i]);
        }
        // base
        loadTexture(gRenderer, baseTexture, PORTAL_PATH);
        loadTexture(gRenderer, getHitTexture, GETTING_HIT_PATH);
        // map
        loadTexture(gRenderer, mapTexture, MAP_PATH);
        loadTexture(gRenderer, roadTexture, ROAD_PATH);
        loadTexture(gRenderer, selectMapMenuTexture, SELECT_MAP_MENU_PATH);
        // gun
        loadTexture(gRenderer, baseGunTexture, GUN_BASE_PATH);
        loadTexture(gRenderer, rocketNotFireTexture, ROCKET_FIRST);
        loadTexture(gRenderer, updateBoardTexture, UPDATE_BOARD_PATH);
        loadTexture(gRenderer, updateButtonTexture, INC_BUTTON_PATH);
        loadTexture(gRenderer, leverTexture, LEVER_PATH);
        loadTexture(gRenderer, blockTexture, BLOCK_PATH);
        loadTexture(gRenderer, trashTexture, DELETE_PATH);
        for (int i = 0; i < 4; i++) {
            loadTexture(gRenderer, gunTexture[i][0], GUN_PATH[i][0]);
            loadTexture(gRenderer, gunTexture[i][1], GUN_PATH[i][1]);
        }
        // supporter
        loadTexture(gRenderer, baseSupporterTexture, SUP_BASE_PATH);
        for (int i = 0; i < 9; i++) {
            loadTexture(gRenderer, supporterTexture[0][i], SUP_DAME_PATH[i]);
            supporterTexture[1][i] = NULL;
        }
        loadTexture(gRenderer, supporterTexture[1][0], SUP_RANGE_PATH);
        // enemy
        for (int i = 0; i < ENEMY_NUM; i++) loadTexture(gRenderer, enemyTexture[i], ENEMY_PATH[i]);
        // bullet
        for (int i = 0; i < BULLET_NUM; i++) loadTexture(gRenderer, bulletTexture[i], BULLET_PATH[i]);


        SDL_SetTextureBlendMode(rangeCircleTexture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(rangeCircleTexture, 40);

        SDL_SetTextureBlendMode(getHitTexture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(getHitTexture, 60);
    }
    ~gameTexture() {
        // menu
        SDL_DestroyTexture(menuTexture);
        SDL_DestroyTexture(optionsMenuTexture);
        SDL_DestroyTexture(playButtonTexture);
        SDL_DestroyTexture(resumeButtonTexture);
        SDL_DestroyTexture(selectMapButtonTexture);
        SDL_DestroyTexture(optionsButtonTexture);
        SDL_DestroyTexture(quitButtonTexture);
        SDL_DestroyTexture(muteTexture);
        // control board
        SDL_DestroyTexture(controlBoardTexture);
        SDL_DestroyTexture(pauseButtonTexture);
        SDL_DestroyTexture(pauseMenuTexture);
        SDL_DestroyTexture(hpBarTexture);
        SDL_DestroyTexture(rangeCircleTexture);
        SDL_DestroyTexture(lockGunTexture);
        for (int i = 0; i < 2; i++) SDL_DestroyTexture(nextButtonTexture[i]);
        for (int i = 0; i < 6; i++) {SDL_DestroyTexture(towerTexture[i]); SDL_DestroyTexture(reviewBoardTexture[i]);}
        // base
        SDL_DestroyTexture(baseTexture);
        // map
        SDL_DestroyTexture(mapTexture);
        SDL_DestroyTexture(roadTexture);
        SDL_DestroyTexture(selectMapMenuTexture);
        // gun
        SDL_DestroyTexture(baseGunTexture);
        SDL_DestroyTexture(rocketNotFireTexture);
        SDL_DestroyTexture(updateBoardTexture);
        SDL_DestroyTexture(updateButtonTexture);
        SDL_DestroyTexture(leverTexture);
        SDL_DestroyTexture(blockTexture);
        SDL_DestroyTexture(trashTexture);
        for (int i = 0; i < 4; i++) {SDL_DestroyTexture(gunTexture[i][0]); SDL_DestroyTexture(gunTexture[i][1]);}
        // supporter
        SDL_DestroyTexture(baseSupporterTexture);
        for (int i = 0; i < 9; i++) {SDL_DestroyTexture(supporterTexture[0][i]); SDL_DestroyTexture(supporterTexture[1][i]);}
        // enemy
        for (int i = 0; i < ENEMY_NUM; i++) SDL_DestroyTexture(enemyTexture[i]);
        // bullet
        for (int i = 0; i < BULLET_NUM; i++) SDL_DestroyTexture(bulletTexture[i]);
    }


    // menu
    SDL_Texture* menuTexture = NULL;
    SDL_Texture* optionsMenuTexture = NULL;
    SDL_Texture* playButtonTexture = NULL;
    SDL_Texture* resumeButtonTexture = NULL;
    SDL_Texture* selectMapButtonTexture = NULL;
    SDL_Texture* optionsButtonTexture = NULL;
    SDL_Texture* quitButtonTexture = NULL;
    SDL_Texture* muteTexture = NULL;
    // control board
    SDL_Texture* controlBoardTexture = NULL;
    SDL_Texture* pauseButtonTexture = NULL;
    SDL_Texture* pauseMenuTexture = NULL;
    SDL_Texture* hpBarTexture = NULL;
    SDL_Texture* rangeCircleTexture = NULL;
    SDL_Texture* lockGunTexture = NULL;
    SDL_Texture* nextButtonTexture[2];
    SDL_Texture* towerTexture[6];
    SDL_Texture* reviewBoardTexture[6];
    // base
    SDL_Texture* baseTexture = NULL;
    SDL_Texture* getHitTexture = NULL;
    // map
    SDL_Texture* mapTexture = NULL;
    SDL_Texture* roadTexture = NULL;
    SDL_Texture* selectMapMenuTexture = NULL;
    // gun
    SDL_Texture* baseGunTexture = NULL;
    SDL_Texture* rocketNotFireTexture = NULL;
    SDL_Texture* updateBoardTexture = NULL;
    SDL_Texture* updateButtonTexture = NULL;
    SDL_Texture* leverTexture = NULL;
    SDL_Texture* blockTexture = NULL;
    SDL_Texture* trashTexture = NULL;
    SDL_Texture* gunTexture[4][2];
    // supporter
    SDL_Texture* baseSupporterTexture = NULL;
    SDL_Texture* supporterTexture[2][9];
    // enemy
    SDL_Texture* enemyTexture[ENEMY_NUM];
    // bullet
    SDL_Texture* bulletTexture[BULLET_NUM];

};