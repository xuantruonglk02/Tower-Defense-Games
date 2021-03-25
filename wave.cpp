#include "wave.h"

bool readWaveData(vector <Wave> &wave) {
    ifstream finp("wave.in");
    if (finp.fail()) {
        printf(" -failed to open wave.in\n");
        return false;
    }
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
    return true;
}
