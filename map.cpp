#include "map.h"

Map::Map() {}
Map::~Map() {}

void Map::readFromFile(string path, bool &quit) {
    ifstream finp(path);
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

void Map::drawToRender(SDL_Renderer* &gRenderer, gameTexture* &gTexture) {
    // draw map background
    SDL_RenderCopy(gRenderer, gTexture->mapTexture, NULL, NULL);
    // draw road
    dstrect.h = 50; dstrect.w = 50;
    dstrect.x = PLAY_ZONE_X;
    dstrect.y = yRoad[0] * 50 + PLAY_ZONE_Y;
    SDL_RenderCopy(gRenderer, gTexture->roadTexture, NULL, &dstrect);

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
            SDL_RenderCopy(gRenderer, gTexture->roadTexture, NULL, &dstrect);
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
int Map::getDir(int pos) {
    if (pos == dir.size()) return 1;
    else return dir[pos];
}