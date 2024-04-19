#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player {

    private:
        std::string name;
        int speed;
        int coveredDistance;
        int totalPowerUps;
        int totalNerfs;

    public:
        int stolenSpeed = 0;

        Player(std::string name)
            : name(name), speed(0), coveredDistance(0), totalPowerUps(0), totalNerfs(0){
        }

        ~Player(){
        }

        std::string getName() const;
        int getSpeed() const;
        int getCoveredDistance() const;
        int getPowerUps() const;
        int getTotalNerfs() const;
        void setSpeed(int speed);
        void setCoveredDistance(int coveredDistance);
        void setName(std::string name);
        void setPowerUps(int totalPowerUps);
        void setTotalNerfs(int totalNerfs);
        void addCoveredDistance(int speed); 
};


#endif // PLAYER_H