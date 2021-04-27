#pragma once

#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::ifstream;

struct Wave {
    bool started = false;
    bool timeStarted = false;
    bool nextWave = false;
    int typeCalling = 0, called = 0;
    int amountOfType;
    vector <int> enemyType;
    vector <int> amountOfEnemy;

    int nextEnemy();
        
};

void readWaveData(vector <Wave> &wave, bool &quit);