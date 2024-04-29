#include "interface.h"

int Interface::printMenu() {

    int choice = 1;
    while (true) {
        clear(); // Clear the screen

        attron(A_BOLD); // Bold text
        printw("\n ________  _____                 ___  __    ________  ________  _________   ");
        printw("\n|\\  _____\\/ __  \\               |\\  \\|\\  \\ |\\   __  \\|\\   __  \\|\\___   ___\\ ");
        printw("\n\\ \\  \\__/|\\/_|\\  \\  ____________\\ \\  \\/  /|\\ \\  \\|\\  \\ \\  \\|\\  \\|___ \\  \\_| ");
        printw("\n \\ \\   __\\|/ \\ \\  \\|\\____________\\ \\   ___  \\ \\   __  \\ \\   _  _\\   \\ \\  \\  ");
        printw("\n  \\ \\  \\_|    \\ \\  \\|____________|\\ \\  \\\\ \\  \\ \\  \\ \\  \\ \\  \\\\  \\|   \\ \\  \\ ");
        printw("\n   \\ \\__\\      \\ \\__\\              \\ \\__\\\\ \\__\\ \\__\\ \\__\\ \\__\\\\ _\\    \\ \\__\\");
        printw("\n    \\|__|       \\|__|               \\|__| \\|__|\\|__|\\|__|\\|__|\\|__|    \\|__|\n\n\n");
        attroff(A_BOLD); // Turn off bold text

        /*

         ________  _____                 ___  __    ________  ________  _________   
        |\  _____\/ __  \               |\  \|\  \ |\   __  \|\   __  \|\___   ___\ 
        \ \  \__/|\/_|\  \  ____________\ \  \/  /|\ \  \|\  \ \  \|\  \|___ \  \_| 
         \ \   __\|/ \ \  \|\____________\ \   ___  \ \   __  \ \   _  _\   \ \  \  
          \ \  \_|    \ \  \|____________|\ \  \\ \  \ \  \ \  \ \  \\  \|   \ \  \ 
           \ \__\      \ \__\              \ \__\\ \__\ \__\ \__\ \__\\ _\    \ \__\
            \|__|       \|__|               \|__| \|__|\|__|\|__|\|__|\|__|    \|__|

        */
                                                                                    
                                                                    
        for (int i = 1; i <= 3; ++i) {
            printw("      ");
            if (i == choice) {
                printw("=> ");
                attron(A_REVERSE); // Highlight current option
            }
            switch (i) {
            case 1:
                printw("Simulate race\n");
                break;
            case 2:
                printw("Credits\n");
                break;
            case 3:
                printw("Exit\n");
                break;
            }
            if (i == choice) {
                attroff(A_REVERSE); // Turn off highlighting
            }
        }

        int ch = getch();

        if (ch == 'q' || ch == 'Q') {
            endwin(); // End ncurses
            return 3; // Exit the program
        } else if (ch == KEY_UP || ch == 'w' || ch == 'W') {
            if (choice == 1) {
                choice = 3;
            } else {
                choice--;
            }
        } else if (ch == KEY_DOWN || ch == 's' || ch == 'S') {
            if (choice == 3) {
                choice = 1;
            } else {
                choice++;
            }
        } else if (ch == '\n' && choice >= 1 && choice <= 3) {
            return choice; // Return the selected option
        }

        refresh(); // Refresh the screen
    }
    return choice;
}

std::vector<Player> Interface::getPositions(std::vector<Player> players) {
    std::sort(players.begin(), players.end(), [](const Player &a, const Player &b) {
        return a.getCoveredDistance() > b.getCoveredDistance();
    });
    return players;
}

void Interface::printStartingGrid(std::vector<Player> &players) {

    for (int i = 0; i < 3; i++) {
        clear(); // Clear the screen
        std::vector<std::string> track(players.size(), "");

        for (size_t i = 0; i < players.size(); ++i) {
            int distance = players[i].getCoveredDistance();
            int position = distance / 10;
            track[i] = std::string(position, '-') + players[i].getName() + " " + std::to_string(players[i].getCoveredDistance()) + "m";
        }

        int color = 1; // Red
        if (i == 1) {
            color = 4; // Yellow
        } else if (i == 2) {
            color = 3; // Green
        }

        printw("\n");
        attron(COLOR_PAIR(color));
        printw("                                ╔═════════════════════════════════════════════════════════════════════╗\n");
        printw("                                ║                               F1-Kart                               ║\n");
        printw("                                ╚═════════════════════════════════════════════════════════════════════╝\n");
        printw("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        for (const auto &lane : track) {
            printw("║▄▀▄-%-129s║\n", lane.c_str());
        }
        printw("╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

        printw("\n");                                                  
        printw("                                           ███████              ███████              ███████\n");
        printw("                                         ███████████          ███████████          ███████████\n");
        printw("                                        █████████████        █████████████        █████████████\n");
        printw("                                        █████████████        █████████████        █████████████\n");
        printw("                                         ███████████          ███████████          ███████████\n");
        printw("                                           ███████              ███████              ███████\n");
        
        attroff(COLOR_PAIR(color));

        refresh(); // Refresh the screen
        sleep(1);
    }
}

void Interface::printRaceTrack(std::vector<Player> &players) {
    clear(); // Clear the screen

    std::vector<std::string> track(players.size(), "");
    for (size_t i = 0; i < players.size(); ++i) {
        int distance = players[i].getCoveredDistance();
        int position = distance / 10;
        track[i] = std::string(position, '-') + players[i].getName() + " " + std::to_string(players[i].getCoveredDistance()) + "m";
    }

    printw("\n");
    printw("                                ╔═════════════════════════════════════════════════════════════════════╗\n");
    printw("                                ║                               F1-Kart                               ║\n");
    printw("                                ╚═════════════════════════════════════════════════════════════════════╝\n");

    printw("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    for (const auto &lane : track) {
        printw("║▄▀▄-%-129s║\n", lane.c_str());
    }
    printw("╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    refresh(); // Refresh the screen
}

void Interface::printLeaderBoard(std::vector<Player> &players) {

    players = getPositions(players);

    printw("\n");
    printw("                                ╔═════════════════════════════════════════════════════════════════════╗\n");
    printw("                                ║                             Leaderboard                             ║\n");
    printw("                                ╠══════════════════════════════════╦══════════════════════════════════╣\n");

    for (int i = 0; i < players.size() / 2; i++) {

        // Print first half of the leaderboard
        std::string coveredDistance1 = std::to_string(players[i].getCoveredDistance()) + "m";
        std::string playerName1 = players[i].getName();
        int pos1 = i + 1;

        printw("                                ║ Position %2d: %-12s %-7s", pos1, playerName1.c_str(), coveredDistance1.c_str());

        // Print the separator
        printw("║%1s", "");

        // Print the second half of the leaderboard
        std::string coveredDistance2 = std::to_string(players[i + 10].getCoveredDistance()) + "m";
        std::string playerName2 = players[i + 10].getName();
        int pos2 = i + 11;
        printw("Position %2d: %-12s %-7s║\n", pos2, playerName2.c_str(), coveredDistance2.c_str());
    }

    printw("                                ╚══════════════════════════════════╩══════════════════════════════════╝\n");

    refresh(); // Refresh the screen
}

void Interface::printCredits() {
    clear();
    printw("\n Developed by: \n\n");
    printw("   - Luis Fuentes Fuentes\n");
    printw("   - Andres Gonzalez Romero\n");
    printw("   - Gerick Vargas Camacho\n");
}

void Interface::displayGoodbye() {
    clear();
    printw("\n    Goodbye, thank you for using the simulator!");
}

void Interface::backToMenu() {
    printw("\n Press ANY KEY to go back to the main menu...");
    refresh();
    getch(); // Wait for any key press
}