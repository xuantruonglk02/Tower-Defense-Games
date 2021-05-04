#pragma once

#include <iostream>

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 650;

const int PLAY_ZONE_X = 150;
const int PLAY_ZONE_Y = 100;
const int PLAY_ZONE_W = 750;
const int PLAY_ZONE_H = 500;

const std::string WINDOW_TITLE = "Super Tower Defender";
// menu
const std::string MENU_PATH = "images/menu.png";
const std::string O_MENU_PATH = "images/options_menu.png";
const std::string PLAY_PATH = "images/play.png";
const std::string RESUME_PATH = "images/resume.png";
const std::string SELECT_MAP_PATH = "images/select-map.png";
const std::string SELECT_MAP_MENU_PATH = "images/select-map-menu.png";
const std::string OPTIONS_PATH = "images/options.png";
const std::string QUIT_PATH = "images/quit.png";
const std::string MUTE_PATH = "images/mute.png";
// control board
const std::string CTB_PATH = "images/control_board.png";
const std::string PAUSE_PATH = "images/pause.png";
const std::string PAUSE_MENU_PATH = "images/options_menu - Copy.png";
const std::string HPBAR_PATH = "images/hp_bar.png";
const std::string LOCK_PATH = "images/lock.png";
const std::string NEXT_BUTTON_PATH[2] = {"images/next_button_down.png", "images/next_button_up.png"};
const std::string TOWER_PATH[6] = {"images/tower0.png",
                                    "images/tower1.png",
                                    "images/tower2.png",
                                    "images/tower3.png",
                                    "images/tower4.png",
                                    "images/tower5.png"};
const std::string REVIEW_BOARD_PATH[6] = {"images/review0.png",
                                            "images/review1.png",
                                            "images/review2.png",
                                            "images/review3.png",
                                            "images/review4.png",
                                            "images/review5.png"};
// map
const int MAP_NUM = 2;
const std::string MAP_PATH = "images/map.png";
const std::string ROAD_PATH = "images/road2.png";
const std::string MAP_DATA_PATH[MAP_NUM] = {"map/map1.in", "map/map2.in"};
// wave
const std::string WAVE_DATA_PATH[MAP_NUM] = {"wave/map1.in", "wave/map2.in"};
// base
const std::string PORTAL_PATH = "images/portal.png";
const std::string GETTING_HIT_PATH = "images/gethit.png";
//gun
const std::string UPDATE_BOARD_PATH = "images/update_board.png";
const std::string INC_BUTTON_PATH = "images/inc_button.png";
const std::string SHOOTING_RANGE_CIRCLE_PATH = "images/circle.png";
const std::string LEVER_PATH = "images/lever.png";
const std::string BLOCK_PATH = "images/block.png";
const std::string DELETE_PATH = "images/delete.png";

const std::string GUN_BASE_PATH = "images/gun_base.png";
const std::string GUN_PATH[4][2] = {{"images/gun0_1.png", "images/gun0_2.png"},
                                    {"images/gun1_1.png", "images/gun1_2.png"},
                                    {"images/gun2_1.png", "images/gun2_2.png"},
                                    {"images/gun3_1.png", "images/gun3_1.png"}};
const std::string ROCKET_FIRST = "images/rocket_1.png";
// supporter
const std::string SUP_BASE_PATH = "images/supporter_base.png";
const std::string SUP_DAME_PATH[9] = {"images/1.png",
                                        "images/2.png",
                                        "images/3.png",
                                        "images/4.png",
                                        "images/5.png",
                                        "images/6.png",
                                        "images/7.png",
                                        "images/8.png",
                                        "images/9.png"};
const std::string SUP_RANGE_PATH = "images/rada.png";
// enemy
const int ENEMY_NUM = 4;
const std::string ENEMY_PATH[4] = {"images/enemy0.png",
                                    "images/enemy1.png",
                                    "images/enemy2.png",
                                    "images/enemy3.png"};
// bullet
const int BULLET_NUM = 4;
const std::string BULLET_PATH[4] = {"images/bullet.png",
                                    "images/double_bullet.png",
                                    "images/laze.png",
                                    "images/rocket_2.png"};

const std::string BOOM_PATH[5] = {"images/boom_1.png",
                                    "images/boom_2.png",
                                    "images/boom_3.png",
                                    "images/boom_4.png",
                                    "images/boom_5.png"};
// --------------------------------------------------
const int BUTTON_W = 270;
const int BUTTON_H = 70;
const int BUTTON_DISTANCE = 20;
const int OPTIONS_MENU_W = 300, OPTIONS_MENU_H = 200;
const int MUSIC_X = 100, MUSIC_Y = 100, MUSIC_R = 30;
const int SOUND_X = 200, SOUND_Y = 100;
const int SELECT_MAP_MENU_W = 600, SELECT_MAP_MENU_H = 250;
const int MAP_REVIEW_W = 225, MAP_REVIEW_H = 150;
const int MAP_XY[MAP_NUM][2] = {{50, 50}, {325, 50}};

const int REVIEW_BOARD_SIZE[6][2] = {{335, 194}, {335, 194}, {348, 224}, {348, 253}, {348, 188}, {384, 188}};
const int NEXT_BUTTON_W = 130, NEXT_BUTTON_H = 60;
const int TOWER_BOARD_X = 3, TOWER_BOARD_Y = 206;
const int UPDATE_BOARD_W = 130, UPDATE_BOARD_H = 214;
const int DISTANCE = 10;
const int LOCK_W = 27, LOCK_H = 40;
const int WAITING_WAVE_TIME_DEFAULT = 16000;
const int BACK_BUTTON_X = 90, BACK_BUTTON_Y = 140, BACK_BUTTON_W = 120, BACK_BUTTON_H = 40;

const int MAP_ROW = 10;
const int MAP_COL = 15;
const int MAP_SIZE = 150;

const int UPDATE_BOARD_BORDER = 5;
const int INC_BUTTON_SIZE = 30;

const int TRASH_SIZE = 30;
const int GUN_BASE_SIZE = 40;
const int ROCKET_FIRST_H = 52;
const int ROCKET_FIRST_W = 24;
const int GUN_W[4][2] = {{24, 24}, {24, 24}, {24, 24}, {30, 30}};
const int GUN_H[4][2] = {{52, 73}, {52, 81}, {52, 52}, {30, 30}};

const int SUP_SIZE[2] = {40, 54};

const int ENEMY_SIZE = 21;

const int BULLET_SIZE = 8;

const int DOUBLE_BULLET_W = 18;
const int DOUBLE_BULLET_H = 8;
const int ROCKET_W[2] = {24, 24};
const int ROCKET_H[2] = {52, 75};
const int BULLET_SPEED[4] = {20, 20, 0, 5};
const int BOOM_RANGE = 50;

/* ------------------------------------------------------------------------------------------------------ */
const int FIRST_MONEY = 150;

const int G_PRICE[4] = {100, 200, 700, 2500};
const int G_DAMAGE[4] = {50, 110, 200, 1000};
const int G_RANGE[4] = {80, 90, 100, 150};
const int G_SHOT_DELAY_TIME[4] = {50, 50, 1000, 3000};

const int G_INC_DAMAGE[4][4] = {{2, 3, 5, 5},
                                {2, 3, 5, 7},
                                {20, 20, 25, 30},
                                {20, 30, 40, 50}};
const int G_INC_RANGE[4][4] = {{5, 5, 7, 10},
                               {5, 7, 10, 15},
                               {5, 10, 15, 20},
                               {5, 10, 20, 40}};
const int G_DEC_SHOT_DELAY_TIME[4][4] = {{2, 2, 2, 2},
                                         {3, 3, 3, 3},
                                         {30, 50, 100, 150},
                                         {50, 100, 200, 250}};
const int G_UPDATE_PRICE[4][3][4] = {{{10, 20, 50, 100}, {5, 10, 10, 20}, {10, 30, 70, 150}},
                                     {{15, 25, 75, 130}, {5, 10, 10, 20}, {20, 50, 100, 150}},
                                     {{20, 50, 100, 200}, {20, 50, 100, 200}, {10, 30, 70, 150}},
                                     {{30, 70, 200, 500}, {50, 100, 300, 600}, {50, 100, 300, 700}}};

const int S_PRICE[2] = {2000, 2000};
const int S_BUFF[2] = {15, 20};
const int S_RANGE[2] = {150, 150};

const int E_HP[4] = {1400, 2500, 3500, 4500};
const int E_DAMAGE[4] = {10, 20, 30, 40};
const int E_PRIZE[4] = {30, 50, 120, 200};
const double E_SPEED[4] = {1, 1, 2, 1};
