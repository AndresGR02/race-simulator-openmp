#ifndef INTERFACE_H
#define INTERFACE_H

#include <algorithm>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <vector>

#include "player.h"

class Interface {

public:
    int printMenu();
    void printStartingGrid(std::vector<Player> &players);
    void printRaceTrack(std::vector<Player> &players);
    void printLeaderBoard(std::vector<Player> &players);
    void printCredits();
    void displayGoodbye();
    void backToMenu();

private:
    std::vector<Player> getPositions(std::vector<Player> players);
};

#endif // INTERFACE_H