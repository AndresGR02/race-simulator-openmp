#include "simulator.h"

#include  "interface.h"

int main() {
    Interface interface;

    while (true){
        int option = interface.printMenu();
        if (option == 1) {
            Simulator simulator;
            simulator.simulateRace();
            interface.backToMenu();
        }
        else if (option == 2) {
            interface.printCredits();
            interface.backToMenu();
        }
        else if (option == 3){
            std::cout << "\n    Goodbye, thank you for using the simulator!" << std::endl;
            break;
        }
    }

    return 0;
}