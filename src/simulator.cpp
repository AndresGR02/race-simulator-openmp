#include "simulator.h"

int totalDistance = 1000;
int speedPowerUp = 100;
int nerfPowerUp = 50;
bool gameOver = false;

void Simulator::resetGlobalVariables() {
    totalDistance = 1000;
    speedPowerUp = 100;
    nerfPowerUp = 50;
    gameOver = false;
}

std::vector<Player> Simulator::getPositions(std::vector<Player> players) {
    std::sort(players.begin(), players.end(), [](const Player &a, const Player &b) {
        return a.getCoveredDistance() > b.getCoveredDistance();
    });
    return players;
}

int Simulator::getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

std::vector<Player> Simulator::createPlayers() {

    std::vector<Player> players;

    std::vector<std::string> protagonistNames = {
        "Alonso", "Link", "Luigi", "Zelda", "Hamilton",
        "Yoshi", "Samus", "Drake", "Kratos", "Pikachu",
        "Goku", "Sonic", "Doomguy", "Ezio",
        "Gordon", "Aloy", "Verstappen", "Sora", "Ellie", "Rayman"};

    while (protagonistNames.size() > 0) {
        int randomIndex = this->getRandomNumber(0, protagonistNames.size() - 1);
        players.push_back(Player(protagonistNames[randomIndex]));
        protagonistNames.erase(protagonistNames.begin() + randomIndex);
    }

    return players;
}

void Simulator::simulateRace() {

    Interface interface;
    std::vector<Player> players = this->createPlayers();

    #pragma omp parallel num_threads(players.size())
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        int player_index = thread_id;

        Player &currentPlayer = players[player_index];

        #pragma omp single
        {
            interface.printStartingGrid(players);
        }

        while (currentPlayer.getCoveredDistance() < totalDistance && !gameOver) {
            int randomNumber = this->getRandomNumber(1, 100);

            if (currentPlayer.getCoveredDistance() > 500 && currentPlayer.getPowerUps() == 0) {
            #pragma omp critical
                {
                    currentPlayer.setPowerUps(1);
                    randomNumber = randomNumber + (0.20 * speedPowerUp);
                    speedPowerUp = speedPowerUp - (0.20 * speedPowerUp);
                }
            }

            #pragma omp critical
            {
                if (currentPlayer.getCoveredDistance() > 750 && currentPlayer.getTotalNerfs() == 0 && nerfPowerUp > 0) {
                    currentPlayer.setTotalNerfs(1);
                    randomNumber = randomNumber - nerfPowerUp;
                    nerfPowerUp = 0;
                }
            }

            if (gameOver) {
                break;
            }

            currentPlayer.setSpeed(randomNumber);
            currentPlayer.addCoveredDistance(currentPlayer.getSpeed());

            #pragma omp master
            {
                // std::vector<Player> sortedPlayers = this->getPositions(players);
                // interface.printRaceTrack(sortedPlayers);

                interface.printRaceTrack(players);
            }

            sleep(1);
        }

        #pragma omp critical
        {
            gameOver = true;
        }
    }
    
    interface.printRaceTrack(players);
    interface.printLeaderBoard(players);

    this->resetGlobalVariables();
}