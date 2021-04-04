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
    Map(SDL_Renderer* &gRenderer);
    ~Map();

    // read map data
    void readFromFile(bool &quit);

    // draw the map
    void drawToRender(SDL_Renderer* &gRenderer);

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

private:
    // map texture
    SDL_Texture* mapTexture = NULL;
    // road texture
    SDL_Texture* roadTexture = NULL;

    SDL_Rect dstrect;

    // array of direction value for enemy moving
    vector<int> dir;
    // array of road position
    vector<int> xRoad, yRoad;
};