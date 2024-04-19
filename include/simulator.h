#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <vector>
#include <iostream>
#include <random>
#include <unistd.h>
#include <vector>
#include <omp.h>

#include "player.h"
#include "interface.h"

class Simulator {
    
public:
    void simulateRace();
    std::vector<Player> createPlayers(); 

private:
    int getRandomNumber(int min, int max);
};

#endif // SIMULATOR_H