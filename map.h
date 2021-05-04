#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "config.h"
#include "utils.h"
#include "texture.h"
#include "enemy.h"

using std::vector;
using std::ifstream;
using std::string;

class Map {
public:
    Map();
    ~Map();

    // read map data
    void readFromFile(string path, bool &quit);

    // draw the map
    void drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture);

    // build the map of road on two-dimensional array
    void buildMapOfObject(int* mapOfObject);

    // get for the enemy moving
    vector<int> getXRoad();
    vector<int> getYRoad();
    vector<int> getDir() ;

    // where the enemy start
    int getYFirst();
    // where the enemy finish
    int getYLast();
    // get direction
    int getDir(int pos);

private:

    SDL_Rect dstrect;

    // array of direction value for enemy moving
    vector<int> dir;
    // array of road position
    vector<int> xRoad, yRoad;
};