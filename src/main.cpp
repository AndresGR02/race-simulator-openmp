#include <iostream>
#include <random>
#include <unistd.h>
#include <vector>
#include <omp.h>

int speedPowerUp = 100;
int totalDistance = 1000;
bool gameOver = false;

class Player 
{
private:
    std::string name;
    int speed;
    int coveredDistance;

public:
    Player(std::string name) 
        : name(name), speed(0), coveredDistance(0) 
    {
    }

    ~Player() 
    {
    }
    
    std::string getName() {
        return name;
    }
    int getSpeed() {
        return speed;        
    } 
    int getCoveredDistance() {
        return coveredDistance;
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

    void addCoveredDistance(int speed) {
        this->coveredDistance += speed;
    }
};

std::vector<Player> podium;
std::vector<std::string> finishLine;

void printRaceTrack(std::vector<Player>& players) {
    std::vector<std::string> track(players.size(), "");
    for (size_t i = 0; i < players.size(); ++i) {
        int distance = players[i].getCoveredDistance();
        int position = distance / 10; 
        track[i] = std::string(position, '-') + players[i].getName();
    }

    for (const auto& lane : track) {
        std::cout << "▓▓" << lane << std::endl;
    }
}

int main() 
{
    Player player("Mario");
    Player player2("Luigi");
    Player player3("Bowser");
    Player player4("Yoshi");

    std::vector<Player> players;

    players.push_back(player);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);

    #pragma omp parallel num_threads(4) 
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        int chunk_size = players.size() / num_threads;
        int start_index = thread_id * chunk_size;
        int end_index = (thread_id == num_threads - 1) ? players.size() : (thread_id + 1) * chunk_size;

        Player& currentPlayer = players[start_index];

        std::cout << "Player " + currentPlayer.getName() + " started" << std::endl;

        while(currentPlayer.getCoveredDistance() < totalDistance && !gameOver) 
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(1, 100);
            int randomNumber = dist(gen);

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

    for(Player p : podium) {
        std::cout << "Player " + p.getName() + " won" << std::endl;
        std::cout << "Distance covered: " + std::to_string(p.getCoveredDistance()) << std::endl;
    }

    return 0;
}
