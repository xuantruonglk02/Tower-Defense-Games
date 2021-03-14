#pragma once

#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 650;

const int PLAY_ZONE_X = 200;
const int PLAY_ZONE_Y = 100;
const int PLAY_ZONE_W = 700;
const int PLAY_ZONE_H = 500;
const double PLAY_ZONE_DIAGONAL = sqrt(PLAY_ZONE_W*PLAY_ZONE_W + PLAY_ZONE_H*PLAY_ZONE_H);

const int BUTTON_W = 270;
const int BUTTON_H = 70;
const int PLAYER_SIZE = 31;
const int BULLET_SIZE = 13;
const int STEP = 2;
const int BULLET_SPEED = 10;

const std::string WINDOW_TITLE = "An Implementation of Code.org Painter";
const std::string WELCOME = "assets/welcome.png";
const std::string PLAY = "assets/play.png";
const std::string OPTIONS = "assets/options.png";
const std::string QUIT = "assets/quit.png";
const std::string PAUSE = "assets/pause.png";
const std::string BACKGROUND1 = "assets/background.png";
const std::string BACKGROUND2 = "assets/background2.png";
const std::string PLAYER_PATH = "assets/player.png";
const std::string BULLET_PATH = "assets/bullet.png";