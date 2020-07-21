#include "Player.h"

Player::Player(std::string name, char mark) : _name(name), _mark(mark){
    std::cout<<"Welcome "<<name<<"!\n";
}

std::string Player::getName() const{
    return _name;
}

char Player::getMark() const{
    return _mark;
}

bool Player::getWinFlag() const{
    return winFlag;
}

void Player::setWinFlag(bool val){
    winFlag = val;
}
