#include "wave.h"

void readWaveData(vector <Wave> &wave, bool &quit) {
    ifstream finp("wave/map1.in");
    if (finp.fail()) {printf(" -failed to open wave.in\n"); quit = true; return;}
    int n_wave;
    finp >> n_wave;
    for (int i = 0; i < n_wave; i++) {
        Wave re;
        finp >> re.amountOfType;
        for (int j = 0; j < re.amountOfType; j++) {
            int a, b;
            finp >> a >> b;
            re.enemyType.push_back(a);
            re.amountOfEnemy.push_back(b);
        }
        wave.push_back(re);
    }
    finp.close();
}

int Wave::nextEnemy() {
    if (typeCalling == amountOfType-1 && amountOfEnemy[typeCalling] == 1) nextWave = true;
    if (amountOfEnemy[typeCalling] == 0) {
        typeCalling++;
    }
    amountOfEnemy[typeCalling]--;
    return enemyType[typeCalling];
}
