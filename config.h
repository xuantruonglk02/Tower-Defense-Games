                #pragma once

#include <iostream>

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 650;

const int PLAY_ZONE_X = 150;
const int PLAY_ZONE_Y = 100;
const int PLAY_ZONE_W = 750;
const int PLAY_ZONE_H = 500;

const std::string WINDOW_TITLE = "GoodGame.com";
const std::string MENU_PATH = "images/menu.png";
const std::string O_MENU_PATH = "images/options_menu.png";
const std::string PLAY_PATH = "images/play.png";
const std::string OPTIONS_PATH = "images/options.png";
const std::string QUIT_PATH = "images/quit.png";
const std::string MUTE_PATH = "images/die.png";

const std::string CTB_PATH = "images/control_board.png";
const std::string PAUSE_PATH = "images/pause.png";
const std::string HPBAR_PATH = "images/hp_bar.png";
const std::string LOCK_PATH = "images/lock.png";
const std::string NEXT_BUTTON_PATH[2] = {"images/next_button_down.png", "images/next_button_up.png"};
const std::string TOWER_PATH[6] = {"images/tower0.png",
                                    "images/tower1.png",
                                    "images/tower2.png",
                                    "images/tower3.png",
                                    "images/tower4.png",
                                    "images/tower5.png"};
const std::string REVIEW_BOARD_PATH[6] = {"images/info.png",
                                            "images/info.png",
                                            "images/info.png",
                                            "images/info.png",
                                            "images/info.png",
                                            "images/info.png"};

const std::string MAP_PATH = "images/map.png";
const std::string ROAD_PATH = "images/road.png";

const std::string UPDATE_BOARD_PATH = "images/update_board.png";
const std::string INC_BUTTON_PATH = "images/inc_button.png";
const std::string SHOOTING_RANGE_CIRCLE_PATH = "images/circle.png";
const std::string LEVER_PATH = "images/lever.png";
const std::string BLOCK_PATH = "images/block.png";

const std::string GUN_BASE_PATH = "images/gun_base.png";
const std::string GUN_PATH[4][2] = {{"images/gun0_1.png", "images/gun0_2.png"},
                                    {"images/gun1_1.png", "images/gun1_2.png"},
                                    {"images/gun2_1.png", "images/gun2_2.png"},
                                    {"images/gun3_1.png", "images/gun3_1.png"}};
const std::string ROCKET_FIRST = "images/rocket_1.png";

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

const std::string ENEMY_PATH[3] = {"images/enemy1.png",
                                    "images/enemy2.png",
                                    "images/enemy3.png"};

const std::string BULLET_PATH[4] = {"images/bullet.png",
                                    "images/double_bullet.png",
                                    "images/laze.png",
                                    "images/rocket_2.png"};

const std::string BOOM_PATH[5] = {"images/boom_1.png",
                                    "images/boom_2.png",
                                    "images/boom_3.png",
                                    "images/boom_4.png",
                                    "images/boom_5.png"};

const int BUTTON_W = 270;
const int BUTTON_H = 70;
const int BUTTON_DISTANCE = 20;
const int OPTIONS_MENU_W = 300, OPTIONS_MENU_H = 200;
const int MUSIC_X = 100, MUSIC_Y = 100, MUSIC_R = 30;
const int SOUND_X = 200, SOUND_Y = 100;

const int REVIEW_BOARD_SIZE[6][2] = {{100, 100}, {200, 200}, {100, 200}, {200, 100}, {300, 300}, {150, 200}}; // w - h
const int NEXT_BUTTON_W = 130, NEXT_BUTTON_H = 60;
const int TOWER_BOARD_X = 3, TOWER_BOARD_Y = 206;
const int UPDATE_BOARD_W = 130, UPDATE_BOARD_H = 214;
const int DISTANCE = 10;
const int LOCK_W = 27, LOCK_H = 40;
const int WAITING_WAVE_TIME_DEFAULT = 16000;

const int MAP_ROW = 10;
const int MAP_COL = 15;
const int MAP_SIZE = 150;

const int UPDATE_BOARD_BORDER = 5;
const int INC_BUTTON_SIZE = 30;

const int GUN_BASE_SIZE = 40;
const int ROCKET_FIRST_H = 52;
const int ROCKET_FIRST_W = 24;
const int GUN_W[4][2] = {{24, 24}, {24, 24}, {24, 24}, {30, 30}};
const int GUN_H[4][2] = {{52, 73}, {52, 81}, {52, 52}, {30, 30}};

const int SUP_SIZE[2] = {40, 54};

const int ENEMY_SIZE = 21;
const int E_HP[3] = {100, 300, 700};
const int E_DAMAGE[3] = {10, 20, 30};
const int E_PRIZE[3] = {1, 2, 3};
const double E_SPEED[3] = {1, 2, 1};

const int BULLET_SIZE = 8;
const int DOUBLE_BULLET_W = 18;
const int DOUBLE_BULLET_H = 8;
const int ROCKET_W[2] = {24, 24};
const int ROCKET_H[2] = {52, 75};
const int BULLET_SPEED[4] = {20, 20, 0, 5};
const int BOOM_RANGE = 50;

const int G_PRICE[4] = {2, 4, 6, 8};
const int G_DAMAGE[4] = {1, 2, 3, 100};
const int G_RANGE[4] = {90, 100, 100, 300};
const int G_SHOT_DELAY_TIME[4] = {50, 50, 300, 3000};

const int G_INC_DAMAGE[4][4] = {{1, 2, 3, 4},
                              {1, 2, 3, 4},
                              {1, 2, 3, 4},
                              {1, 2, 3, 4}};
const int G_INC_RANGE[4][4] = {{10, 10, 10, 10},
                                {10, 10, 10, 10},
                                {10, 10, 10, 10},
                                {10, 10, 10, 10}};
const int G_DEC_SHOT_DELAY_TIME[4][4] = {{5, 5, 5, 5},
                                        {50, 50, 50, 50},
                                        {50, 50, 50, 50},
                                        {50, 50, 50, 50}};
const int G_UPDATE_PRICE[4][3][4] = {{{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}}, // gun 0 - dame - speed - range
                                     {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}},
                                     {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}},
                                     {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}}};

const int S_PRICE[2] = {10, 15};
const int S_BUFF[2] = {5, 10};
const int S_RANGE[2] = {200, 200};

const int S_UPDATE_PRICE[2][4] = {{4, 6, 8, 10},
                                  {4, 6, 8, 10}};
const int S_INC_BUFF[2][4] = {{5, 5, 5, 5},
                                {10, 10, 20, 30}};
const int S_INC_RANGE[2][4] = {{10, 10, 10, 10},
                                {10, 10, 10, 10}};