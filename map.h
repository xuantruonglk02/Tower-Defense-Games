#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"

using std::vector;
using std::ifstream;

class Map {
public:
    Map(SDL_Renderer* &gRenderer, bool &quit);
    ~Map();

    void readFromFile(bool &quit);
    void drawToRender(SDL_Renderer* &gRenderer);
    vector<int> getXRoad();
    vector<int> getYRoad();
    vector<int> getDir() ;
    int getYFirst();
    int getYLast();
private:
    SDL_Texture* mapTexture = NULL;
    SDL_Texture* rvTexture = NULL;

    SDL_Rect dstrect;

    vector<int> dir;
    vector<int> xRoad, yRoad;
};