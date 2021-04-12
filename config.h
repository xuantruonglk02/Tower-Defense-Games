#pragma once

#include <iostream>

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 650;

const int PLAY_ZONE_X = 150;
const int PLAY_ZONE_Y = 100;
const int PLAY_ZONE_W = 750;
const int PLAY_ZONE_H = 500;

const int BUTTON_W = 270;
const int BUTTON_H = 70;
const int GUN_SIZE = 40;
const int ENEMY_SIZE = 31;
const int BULLET_SIZE = 13;
const int BULLET_SPEED[] = {10};

const std::string WINDOW_TITLE = "An Implementation of Code.org Painter";
const std::string MENU_PATH = "images/menu.png";
const std::string O_MENU_PATH = "images/options_menu.png";
const std::string PLAY_PATH = "images/play.png";
const std::string OPTIONS_PATH = "images/options.png";
const std::string QUIT_PATH = "images/quit.png";
const std::string PAUSE_PATH = "images/pause.png";
const std::string MAP_PATH = "images/map.png";
const std::string CTB_PATH = "images/control_board.png";
const std::string BASE_PATH = "images/base.png";
const std::string HPBAR_PATH = "images/hp_bar.png";
const std::string LOCK_PATH = "images/lock.png";
const std::string ROAD_PATH = "images/road.png";
const std::string UPDATE_BOARD_PATH = "images/update_board.png";
const std::string INC_BUTTON_PATH = "images/inc_button.png";
const std::string SHOOTING_RANGE_CIRCLE_PATH = "images/circle.png";
const std::string LEVER_PATH = "images/lever.png";
const std::string BLOCK_PATH = "images/block.png";
const std::string GUN_PATH[6] = {"images/gun1.png",
                                    "images/gun2.png",
                                    "images/gun3.png",
                                    "images/gun4.png",
                                    "images/gun5.png",
                                    "images/gun6.png",};
const std::string ENEMY_PATH[3] = {"images/enemy1.png",
                                    "images/enemy2.png",
                                    "images/enemy3.png"};
const std::string BULLET_PATH = "images/bullet.png";

const int G_PRICE[] = {2, 4, 6, 8, 10, 12};
const int G_DAMAGE[] = {1, 2, 3, 4, 5, 6};
const int G_RANGE[] = {90, 100, 100, 100, 100, 100};
const int G_SHOT_DELAY_TIME[] = {0, 300, 300, 300, 300, 300};

const int G_INC_DAMAGE[][4] = {{1, 2, 3, 4},
                              {1, 2, 3, 4},
                              {1, 2, 3, 4},
                              {1, 2, 3, 4},
                              {1, 2, 3, 4},
                              {1, 2, 3, 4}};
const int G_INC_RANGE[] = {10, 10, 10, 10, 10, 10};
const int G_DEC_SHOT_DELAY_TIME[] = {5, 50, 50, 50, 50, 50};
const int G_UPDATE_PRICE[][4] = {{1, 2, 3, 4},
                                 {1, 2, 3, 4},
                                 {1, 2, 3, 4},
                                 {1, 2, 3, 4},
                                 {1, 2, 3, 4},
                                 {1, 2, 3, 4}};

const int E_HP[] = {100, 300, 700};
const int E_DAMAGE[] = {10, 20, 30};
const int E_SPEED[] = {1, 2, 1};
const int E_PRIZE[] = {1, 2, 3, 4, 5, 6};
