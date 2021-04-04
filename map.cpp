#include "map.h"

Map::Map(SDL_Renderer* &gRenderer) {
    mapTexture = loadTexture(gRenderer, MAP_PATH);
    roadTexture = loadTexture(gRenderer, ROAD_PATH);
}
Map::~Map() {
    SDL_DestroyTexture(mapTexture);
    SDL_DestroyTexture(roadTexture);
    mapTexture = NULL;
    roadTexture = NULL;
}

void Map::readFromFile(bool &quit) {
    ifstream finp("map/map1.in");
    if (finp.fail()) {printf(" -failed to open map1.in\n"); quit = true; return;}
    int n;
    finp >> n;
    for (int i = 0; i < n; i++) {
        int d, a, b;
        finp >> d >> a >> b;
        dir.push_back(d);
        xRoad.push_back(a);
        yRoad.push_back(b);
    }
    finp.close();
}

void Map::drawToRender(SDL_Renderer* &gRenderer) {
    // draw map background
    SDL_RenderCopy(gRenderer, mapTexture, NULL, NULL);
    // draw road
    dstrect.h = 50; dstrect.w = 50;
    dstrect.x = PLAY_ZONE_X;
    dstrect.y = yRoad[0] * 50 + PLAY_ZONE_Y;
    SDL_RenderCopy(gRenderer, roadTexture, NULL, &dstrect);

    for (int i = 1; i < xRoad.size(); i++) {
        int u = xRoad[i-1], v = yRoad[i-1];
        do {
            switch (dir[i]) {
                case 0: v--; break;
                case 1: u++; break;
                case 2: v++; break;
                case 3: u--; break;
            }
            dstrect.x = u * 50 + PLAY_ZONE_X;
            dstrect.y = v * 50 + PLAY_ZONE_Y;
            SDL_RenderCopy(gRenderer, roadTexture, NULL, &dstrect);
        } while (u != xRoad[i] || v != yRoad[i]);
    }
}

void Map::buildMapOfObject(int* mapOfObject) {
    mapOfObject[yRoad[0] * 15 + xRoad[0]] = -1;
    for (int i = 1; i < xRoad.size(); i++) {
        int u = yRoad[i-1], v = xRoad[i-1];
        do {
            switch (dir[i]) {
                case 0: u--; break;
                case 1: v++; break;
                case 2: u++; break;
                case 3: v--; break;
            }
            mapOfObject[u * 15 + v] = -1;
        } while (u != yRoad[i] || v != xRoad[i]);
    }
}

vector<int> Map::getXRoad() {return xRoad;}
vector<int> Map::getYRoad() {return yRoad;}
vector<int> Map::getDir() {return dir;}

int Map::getYFirst() {return yRoad[0];}
int Map::getYLast() {return yRoad[yRoad.size()-1];}