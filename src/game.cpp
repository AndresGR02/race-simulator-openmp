#include "game.h"

Game::Game() {
    this->simulator = new Simulator();
    this->interface = new Interface();
}

Game::~Game() {
    delete this->simulator;
    delete this->interface;
}

void Game::run() {
    while (true){
        int option = interface->printMenu();
        if (option == 1) {
            simulator->simulateRace();
            interface->backToMenu();
        }
        else if (option == 2) {
            interface->printCredits();
            interface->backToMenu();
        }
        else if (option == 3){
            std::cout << "\n    Goodbye, thank you for using the simulator!" << std::endl;
            break;
        }
    }

}

