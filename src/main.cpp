#include <iostream>
#include <random>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <omp.h>

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

void printStartingGrid(std::vector<Player>& players) {
    std::vector<std::string> track(players.size(), "");
    
    for (size_t i = 0; i < players.size(); ++i) {
        int distance = players[i].getCoveredDistance();
        int position = distance / 10; 
        track[i] = std::string(position, '-') + players[i].getName() + " " + std::to_string(players[i].getCoveredDistance()) + "m";
    }

    std::cout << "══════════════════════════════════════════════════════════════════════════════════════════════════════════════" << std::endl;
    for (const auto& lane : track) {
        std::cout << "▄▀▄" << lane << std::endl;
    }
    std::cout << "══════════════════════════════════════════════════════════════════════════════════════════════════════════════" << std::endl;

}

void printRaceTrack(std::vector<Player>& players) {
    std::vector<std::string> track(players.size(), "");
    for (size_t i = 0; i < players.size(); ++i) {
        int distance = players[i].getCoveredDistance();
        int position = distance / 10; 
        track[i] = std::string(position, '-') + players[i].getName() + " " + std::to_string(players[i].getCoveredDistance()) + "m";
    }
    
    std::cout << "══════════════════════════════════════════════════════════════════════════════════════════════════════════════" << std::endl;
    for (const auto& lane : track) {
        std::cout << "▄▀▄" << lane << std::endl;
    }
    std::cout << "══════════════════════════════════════════════════════════════════════════════════════════════════════════════" << std::endl;

    std::cout << "       \e[1;101m******\e[0m       \n" 
                 "     \e[1;101m***********\e[0m     \n"
                 "   \e[1;101m************\e[0m     \n" 
                 "    \e[1;101m*************\e[0m     \n"
                 "     \e[1;101m**********\e[0m      \n"
                 "       \e[1;101m******\e[0m        \n";
}

std::vector<Player> getPositions(std::vector<Player> players) {
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.getCoveredDistance() > b.getCoveredDistance();
    });
    return players;
}

int main() {

    static const std::string protagonistNames[] = {
        "Alonso", "Link", "Luigi", "Zelda", "Leclerc",
        "Yoshi", "Samus", "Drake", "Kratos", "Pikachu",
        "Goku", "Sonic", "Doomguy", "Ezio",
        "Gordon", "Aloy", "Verstappen", "Sora", "Ellie", "Rayman"
    };

    std::vector<Player> players;
    
    for (std::string name : protagonistNames) {
        Player player(name);
        players.push_back(player);
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
            printRaceTrack(players);
            sleep(3);
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

    int i = 0;
    for (Player player : getPositions(players)) {
        std::cout << "Position " << ++i << ": ";
        std::cout << player.getName() << " " << player.getCoveredDistance() << "m" << std::endl;
    }

    return 0;
}

