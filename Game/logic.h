#ifndef LOGIC_H
#define LOGIC_H

#include <cmath>

static bool collision(int playerRadius, int aiRaidius, float* playerVector, float* aiVector) {
    return (fabs(aiVector[0] - playerVector[0]) <= (playerRadius + aiRaidius + aiRaidius) && fabs(aiVector[1] - playerVector[1]) <= (playerRadius + aiRaidius));
}

#endif
