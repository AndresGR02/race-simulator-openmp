#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <unistd.h>
#include <algorithm>

#include "player.h"

class Interface {
    
public:
    int printMenu();
    void printStartingGrid(std::vector<Player>& players);
    void printRaceTrack(std::vector<Player>& players);
    void printLeaderBoard(std::vector<Player>& players);
    void printCredits();
    void backToMenu(); 

private:
    void clearScreen();
    std::vector<Player> getPositions(std::vector<Player> players);
};

#endif // INTERFACE_H