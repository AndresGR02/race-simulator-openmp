#include "player.h"

std::string Player::getName() const{
    return name;
}

int Player::getSpeed() const{
    return speed;
}

int Player::getCoveredDistance() const{
    return coveredDistance;
}

int Player::getPowerUps() const{
    return totalPowerUps;
}

int Player::getTotalNerfs() const{
    return totalNerfs;
}

void Player::setSpeed(int speed){ 
    this->speed = speed;
}

void Player::setCoveredDistance(int coveredDistance){
    this->coveredDistance = coveredDistance;
}

void Player::setName(std::string name){
    this->name = name;
}

void Player::setPowerUps(int totalPowerUps){
    this->totalPowerUps = totalPowerUps;
}

void Player::setTotalNerfs(int totalNerfs){
    this -> totalNerfs = totalNerfs;
}

void Player::addCoveredDistance(int speed){
    this->coveredDistance += speed; 
}
