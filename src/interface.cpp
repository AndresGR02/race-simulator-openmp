#include "interface.h"

int Interface::printMenu() {
    clearScreen();
    std::cout << "\n      F1-Kart\n" << std::endl;
    std::cout << "1. Simulate race" << std::endl;
    std::cout << "2. Credits" << std::endl;
    std::cout << "3. Exit" << std::endl;
    int choice;
    std::cout << std::endl << "Enter your choice: ";
    std::cin >> choice;
    return  choice;
}

void Interface::clearScreen() {
    #if defined(_WIN32)
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #endif
}

std::vector<Player> Interface::getPositions(std::vector<Player> players) {
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.getCoveredDistance() > b.getCoveredDistance();
    });
    return players;
}

void Interface::printStartingGrid(std::vector<Player>& players) {

    for (int i = 0; i < 3; i++) {
        system("clear");
        std::vector<std::string> track(players.size(), "");
        
        for (size_t i = 0; i < players.size(); ++i) {
            int distance = players[i].getCoveredDistance();
            int position = distance / 10; 
            track[i] = std::string(position, '-') + players[i].getName() + " " + std::to_string(players[i].getCoveredDistance()) + "m";
        }

        std::string color = "\033[31m";
        if (i == 1) {
            color = "\033[33m";
        } else if (i == 2) {
            color = "\033[32m";
        }
        
        
        std::cout << std::endl;
        std::cout << color << "                                ╔═════════════════════════════════════════════════════════════════════╗                    " << std::endl;
        std::cout << color << "                                ║                               F1-Kart                               ║                    " << std::endl;
        std::cout << color << "                                ╚═════════════════════════════════════════════════════════════════════╝                    " << std::endl;
        std::cout << color << "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\e[0m" << std::endl;
        for (const auto& lane : track) {
            std::cout <<  color << "║▄▀▄-" << std::left << std::setw(129) << lane << "║" << "\e[0m" << std::endl;
        }
        std::cout << color << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\e[0m" << std::endl;

        std::string bgColor = "\033[41m";
        if (i == 1) {
            bgColor = "\033[43m";
        } else if (i == 2) {
            bgColor = "\033[42m";
        }

        std::cout << std::endl;
        std::cout << "                                           " << bgColor << "*******\e[0m              " << bgColor << "*******\e[0m              " << bgColor << "*******\e[0m           \n"
                    "                                         " << bgColor << "***********\e[0m          " << bgColor << "***********\e[0m          " << bgColor << "***********\e[0m         \n" 
                    "                                        " << bgColor << "*************\e[0m        " << bgColor << "*************\e[0m        " << bgColor << "*************\e[0m        \n" 
                    "                                        " << bgColor << "*************\e[0m        " << bgColor << "*************\e[0m        " << bgColor << "*************\e[0m        \n"
                    "                                         " << bgColor << "***********\e[0m          " << bgColor << "***********\e[0m          " << bgColor << "***********\e[0m         \n"
                    "                                           " << bgColor << "*******\e[0m              " << bgColor << "*******\e[0m              " << bgColor << "*******\e[0m           \n";

        sleep(1);
    
    }


}


void Interface::printRaceTrack(std::vector<Player>& players) {
    system("clear");
    std::vector<std::string> track(players.size(), "");
    for (size_t i = 0; i < players.size(); ++i) {
        int distance = players[i].getCoveredDistance();
        int position = distance / 10; 
        track[i] = std::string(position, '-') + players[i].getName() + " " + std::to_string(players[i].getCoveredDistance()) + "m";
    }

    std::cout << std::endl;
    std::cout << "                                ╔═════════════════════════════════════════════════════════════════════╗                    " << std::endl;
    std::cout << "                                ║                               F1-Kart                               ║                    " << std::endl;
    std::cout << "                                ╚═════════════════════════════════════════════════════════════════════╝                    " << std::endl;
    
    std::cout << "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    for (const auto& lane : track) {
        std::cout << "║▄▀▄-" << std::left << std::setw(129) << lane << "║" << std::endl;
    }
    std::cout << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;

}

void Interface::printLeaderBoard(std::vector<Player>& players){

    players = getPositions(players);

    std::cout << std::endl;
    std::cout << "                                ╔═════════════════════════════════════════════════════════════════════╗                    " << std::endl;
    std::cout << "                                ║                             Leaderboard                             ║                    " << std::endl;
    std::cout << "                                ╠══════════════════════════════════╦══════════════════════════════════╣                    " << std::endl;
    for(int i = 0; i < players.size()/2; i++) {
        std::string index;
        if(i + 1 < 10) {
            index = " " + std::to_string(i + 1);
        } else {
            index = std::to_string(i + 1);
        }

        std::cout << "                                ║ Position " + index + ": " << std::left << std::setw(12) << players[i].getName() + " " << std::setw(8) << std::to_string(players[i].getCoveredDistance()) + "m";
        std::cout << std::left << std::setw(6) << "║";
        std::cout << "Position " + std::to_string(i + 11) + ": " << std::left << std::setw(12) << players[i + 10].getName() + " " << std::setw(6) << std::to_string(players[i + 10].getCoveredDistance()) + "m" << "║" << std::endl;
    }

    std::cout << "                                ╚══════════════════════════════════╩══════════════════════════════════╝                    " << std::endl;
}


void Interface::printCredits() { 
    clearScreen();
    std::cout << std::endl << "Developed by: " << std::endl << std::endl;
    std::cout << "  - Luis Fuentes Fuentes" << std::endl;
    std::cout << "  - Andres Gonzalez Romero" << std::endl;
    std::cout << "  - Gerick Vargas Camacho " << std::endl;
}

void Interface::backToMenu() {
    std::cout << std::endl << "Press ENTER to go back to the main menu...";
    std::cin.ignore().get();
}