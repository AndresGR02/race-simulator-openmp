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

    setlocale(LC_ALL, "");

    initscr(); // Initialize ncurses
    raw(); // Disable line buffering
    keypad(stdscr, TRUE); // Enable keypad for arrow keys

    use_default_colors(); // Use default colors
    start_color(); // Start color mode
    init_pair(1, COLOR_RED, -1); // Define color pair 1 (red)
    init_pair(2, COLOR_BLUE, -1); // Define color pair 2 (blue)
    init_pair(3, COLOR_GREEN, -1); // Define color pair 2 (green)
    init_pair(4, COLOR_YELLOW, -1); // Define color pair 2 (yellow)

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
    
    refresh(); // Refresh the screen
    endwin(); // End ncurses
    
    system("clear");

}

