#include <iostream>
#include <random>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <iomanip>

int speedPowerUp = 100;
int nerfPowerUp = 50;
int totalDistance = 1000;
bool gameOver = false;

class Player 
{
private:
    std::string name;
    int speed;
    int coveredDistance;
    int totalPowerUps;
    int totalNerfs;

public:

    int stolenSpeed = 0;

    Player(std::string name) 
        : name(name), speed(0), coveredDistance(0), totalPowerUps(0), totalNerfs(0) 
    {
    }

    ~Player() 
    {
    }
    
    std::string getName() {
        return name;
    }
    int getSpeed() const {
        return speed;        
    } 
    int getCoveredDistance() const {
        return coveredDistance;
    }
    int getPowerUps() const {
        return totalPowerUps;
    }
    int getTotalNerfs() const {
        return totalNerfs;
    }

    void setSpeed(int speed) {
        this->speed = speed;
    }
    void setCoveredDistance(int coveredDistance) {
        this->coveredDistance = coveredDistance;
    }
    void setName(std::string name) {
        this->name = name;
    }
    void setPowerUps(int totalPowerUps) {
        this->totalPowerUps = totalPowerUps;
    }
    void setTotalNerfs(int totalNerfs) {
        this->totalNerfs = totalNerfs;
    }

    void addCoveredDistance(int speed) {
        this->coveredDistance += speed;
    }
    
};

std::vector<Player> podium;
std::vector<std::string> finishLine;

void printStartingGrid(std::vector<Player>& players, int iteration) {
    std::vector<std::string> track(players.size(), "");
    
    for (size_t i = 0; i < players.size(); ++i) {
        int distance = players[i].getCoveredDistance();
        int position = distance / 10; 
        track[i] = std::string(position, '-') + players[i].getName() + " " + std::to_string(players[i].getCoveredDistance()) + "m";
    }

    std::string color = "\e[1;31m";
    if (iteration == 1) {
        color = "\e[1;32m";
    } else if (iteration == 2) {
        color = "\033[1;33m";
    }
    
    
    std::cout << std::endl;
    std::cout << color << "                    ╔═════════════════════════════════════════════════════════════════════╗                    " << std::endl;
    std::cout << color << "                    ║                               F1-Kart                               ║                    " << std::endl;
    std::cout << color << "                    ╚═════════════════════════════════════════════════════════════════════╝                    " << std::endl;
    std::cout << color << "╔═╦════════════════════════════════════════════════════════════════════════════════════════════════════════════\e[0m" << std::endl;
    for (const auto& lane : track) {
        std::cout <<  color << "▄▀▄-" << lane << "\e[0m" << std::endl;
    }
    std::cout <<  color << "╚═╩════════════════════════════════════════════════════════════════════════════════════════════════════════════\e[0m" << std::endl;

}

void printRaceTrack(std::vector<Player>& players) {
    std::vector<std::string> track(players.size(), "");
    for (size_t i = 0; i < players.size(); ++i) {
        int distance = players[i].getCoveredDistance();
        int position = distance / 10; 
        track[i] = std::string(position, '-') + players[i].getName() + " " + std::to_string(players[i].getCoveredDistance()) + "m";
    }

    std::cout << std::endl;
    std::cout << "                    ╔═════════════════════════════════════════════════════════════════════╗                    " << std::endl;
    std::cout << "                    ║                               F1-Kart                               ║                    " << std::endl;
    std::cout << "                    ╚═════════════════════════════════════════════════════════════════════╝                    " << std::endl;
    
    std::cout << "╔═╦════════════════════════════════════════════════════════════════════════════════════════════════════════════" << std::endl;
    for (const auto& lane : track) {
        std::cout << "▄▀▄-" << lane << std::endl;
    }
    std::cout << "╚═╩════════════════════════════════════════════════════════════════════════════════════════════════════════════" << std::endl;

}

std::vector<Player> getPositions(std::vector<Player> players) {
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.getCoveredDistance() > b.getCoveredDistance();
    });
    return players;
}

int main() {

    std::vector<std::string> protagonistNames = {
        "Alonso", "Link", "Luigi", "Zelda", "Leclerc",
        "Yoshi", "Samus", "Drake", "Kratos", "Pikachu",
        "Goku", "Sonic", "Doomguy", "Ezio",
        "Gordon", "Aloy", "Verstappen", "Sora", "Ellie", "Rayman"
    };

    std::vector<Player> players;
    
    // Add players in random order
    while(protagonistNames.size() > 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, protagonistNames.size() - 1);
        int randomIndex = dist(gen);
        players.push_back(Player(protagonistNames[randomIndex]));
        protagonistNames.erase(protagonistNames.begin() + randomIndex);
    }


    #pragma omp parallel num_threads(players.size()) 
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        int chunk_size = players.size() / num_threads;
        int start_index = thread_id * chunk_size;
        int end_index = (thread_id == num_threads - 1) ? players.size() : (thread_id + 1) * chunk_size;

        Player& currentPlayer = players[start_index];

        #pragma omp single
        {
            for (int i = 0; i < 3; i++) {
                system("clear");
                printStartingGrid(players, i);
                sleep(1);
            }
        }

        while(currentPlayer.getCoveredDistance() < totalDistance && !gameOver) 
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(1, 100);
            int randomNumber = dist(gen);
            
            if (currentPlayer.getCoveredDistance() > 500 && currentPlayer.getPowerUps() == 0) 
            {   
                #pragma omp critical 
                {
                    currentPlayer.setPowerUps(1);
                    randomNumber = randomNumber + (0.5*speedPowerUp);
                    speedPowerUp = speedPowerUp - (0.5*speedPowerUp);         
                }
            } 
        
            #pragma omp critical 
            {
                if (currentPlayer.getCoveredDistance() > 750 && currentPlayer.getTotalNerfs() == 0 && nerfPowerUp > 0) 
                {
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
            
            #pragma omp critical
            {   
                system("clear");
                printRaceTrack(players);
            }

            sleep(1);
        }
        
        #pragma omp critical 
        {
            gameOver = true;
            podium.push_back(players[start_index]);
        }
    }

    std::cout << std::endl;
    std::cout << "                    ╔═════════════════════════════════════════════════════════════════════╗                    " << std::endl;
    std::cout << "                    ║                             Leaderboard                             ║                    " << std::endl;

    std::vector<Player> sortedPlayers = getPositions(players);

    std::cout << "                    ╠══════════════════════════════════╦══════════════════════════════════╣                    " << std::endl;
    for(int i = 0; i < sortedPlayers.size()/2; i++) {
        std::string index;
        if(i + 1 < 10) {
            index = "0" + std::to_string(i + 1);
        } else {
            index = std::to_string(i + 1);
        }

        std::cout << "                    ║ Position " + index + ": " << std::left << std::setw(12) << sortedPlayers[i].getName() + " " << std::setw(8) << std::to_string(sortedPlayers[i].getCoveredDistance()) + "m";
        std::cout << std::left << std::setw(6) << "║";
        std::cout << "Position " + std::to_string(i + 11) + ": " << std::left << std::setw(12) << sortedPlayers[i + 10].getName() + " " << std::setw(6) << std::to_string(sortedPlayers[i + 10].getCoveredDistance()) + "m" << "║" << std::endl;
    }

    std::cout << "                    ╚══════════════════════════════════╩══════════════════════════════════╝                    " << std::endl;
    return 0;
}