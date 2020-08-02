#include "player.h"

player::player() : rowPosition(0), colPosition(0){
}

player::player(const int &rowVal, const int &colVal) : rowPosition(rowVal), colPosition(colVal){
}

int player::getRowPosition() const{
    return rowPosition;
}

int player::getColPosition() const{
    return colPosition;
}

void player::setPosition(const int &rowVal, const int &colVal){
    rowPosition = rowVal;
    colPosition = colVal;
}
