#pragma once

#include <iostream>

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 650;

const int PLAY_ZONE_X = 200;
const int PLAY_ZONE_Y = 100;
const int PLAY_ZONE_W = 700;
const int PLAY_ZONE_H = 500;

const int BUTTON_W = 270;
const int BUTTON_H = 70;
const int GUN_SIZE = 31;
const int ENEMY_SIZE = 31;
const int BULLET_SIZE = 13;
const int BULLET_SPEED[] = {10};

const std::string WINDOW_TITLE = "An Implementation of Code.org Painter";
const std::string WELCOME_PATH = "assets/welcome.png";
const std::string PLAY_PATH = "assets/play.png";
const std::string OPTIONS_PATH = "assets/options.png";
const std::string QUIT_PATH = "assets/quit.png";
const std::string PAUSE_PATH = "assets/pause.png";
const std::string MAP_PATH = "assets/map.png";
const std::string CTBG_PATH = "assets/control_bg.png";
const std::string BASE_PATH = "assets/base.png";
const std::string HPBAR_PATH = "assets/hp_bar.png";
const std::string RIVER_PATH = "assets/river.png";
const std::string GUN_PATH[6] = {"assets/gun1.png",
                                    "assets/gun2.png",
                                    "assets/gun3.png",
                                    "assets/gun4.png",
                                    "assets/gun5.png",
                                    "assets/gun6.png",};
const std::string ENEMY_PATH[3] = {"assets/enemy1.png",
                                    "assets/enemy2.png",
                                    "assets/enemy3.png"};
const std::string BULLET_PATH = "assets/bullet.png";

const int G_DAMAGE[] = {1, 2, 3, 4, 5, 6};
const int E_HP[] = {100, 300, 700};
const int E_DAMAGE[] = {10, 20, 30};
const int E_SPEED[] = {1, 1, 1};