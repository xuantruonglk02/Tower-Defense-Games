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
    int typeCalling = 0;
    int amountOfType;
    vector <int> enemyType;
    vector <int> amountOfEnemy;

    int nextEnemy() {
        if (typeCalling == amountOfType-1
            && amountOfEnemy[typeCalling] == 1) nextWave = true;
        if (amountOfEnemy[typeCalling] == 0) {
            typeCalling++;
        }
        amountOfEnemy[typeCalling]--;
        return typeCalling;
    }
};

bool readWaveData(vector <Wave> &wave);