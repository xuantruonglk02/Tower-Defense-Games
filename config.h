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
const int BULLET_SPEED[] = {10, 5};

const std::string WINDOW_TITLE = "An Implementation of Code.org Painter";
const std::string WELCOME = "assets/welcome.png";
const std::string PLAY = "assets/play.png";
const std::string OPTIONS = "assets/options.png";
const std::string QUIT = "assets/quit.png";
const std::string PAUSE = "assets/pause.png";
const std::string MAP = "assets/map.png";
const std::string CT_BG = "assets/control_bg.png";
const std::string GUN_PATH[6] = {"assets/gun1.png",
                                    "assets/gun2.png",
                                    "assets/gun3.png",
                                    "assets/gun4.png",
                                    "assets/gun5.png",
                                    "assets/gun6.png",};
const std::string ENEMY_PATH[1] = {"assets/enemy.png"};
const int E_HP[1] = {5};
const std::string BULLET_PATH = "assets/bullet.png";