#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <omp.h>
#include <random>
#include <vector>

#include "interface.h"
#include "player.h"

class Simulator {

public:
    void simulateRace();
    std::vector<Player> createPlayers();

private:
    int getRandomNumber(int min, int max);
    void resetGlobalVariables();
    std::vector<Player> getPositions(std::vector<Player> players);
};

#endif // SIMULATOR_H