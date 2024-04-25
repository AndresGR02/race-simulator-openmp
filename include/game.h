#ifndef GAME_H
#define GAME_H

#include "interface.h"
#include "simulator.h"

class Game {
private:
    Simulator* simulator;
    Interface* interface;

public:
    Game(); 
    ~Game();
    void run();
};

#endif 
