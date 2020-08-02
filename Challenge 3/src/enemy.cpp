#include "enemy.h"

enemy::enemy(std::string name, char symbol) : _name(name), _symbol(symbol){
}

enemy::~enemy()
{
    //dtor
}

int enemy::getRowPosition() const{
    return rowPosition;
}

int enemy::getColPosition() const{
    return colPosition;
}

void enemy::setPosition(const int &rowVal, const int &colVal){
    rowPosition = rowVal;
    colPosition = colVal;
}
