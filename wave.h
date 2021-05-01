#pragma once

#include <iostream>
#include <vector>

using std::vector;

struct Wave {
    bool started = false;
    bool timeStarted = false;
    bool nextWave = false;
    int typeCalling = 0, called = 0;
    int amountOfType;
    vector <int> enemyType;
    vector <int> amountOfEnemy;

    void setUpForResume() {
        started = false;
        timeStarted = false;
        nextWave = false;
        typeCalling = 0, called = 0;
    } 

    int nextEnemy() {
        if (typeCalling == amountOfType-1 && called == amountOfEnemy[typeCalling] - 1) nextWave = true;
        if (called == amountOfEnemy[typeCalling]) {
            typeCalling++;
            called = 0;
        }
        called++;
        return enemyType[typeCalling];
    }

};