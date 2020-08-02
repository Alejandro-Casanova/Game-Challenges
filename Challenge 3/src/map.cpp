#include "map.h"

map::map() : stringSize(0), vectorSize(0){

}

bool map::loadMap(std::string fileName){
    std::ifstream inputFile;
    std::string input;

    inputFile.open(fileName);
    if(inputFile.fail()){
        perror(fileName.c_str());
        return 1;
    }
    int maxStringSize = 0;
    while(getline(inputFile, input)){
        if(input.size() > maxStringSize){
            maxStringSize = input.size();//Saves max string size value
        }
        mapLayout.push_back(input);
    }

    //Saves map size in private variables
    setVectorSize(mapLayout.size());
    setMaxStringSize(maxStringSize);
}

void map::printMap() const{
    system("cls");
    for(int i = 0; i < getVectorSize(); i++){
        std::cout << mapLayout[i] << std::endl;
    }
}

bool map::initPlayer(player &playerObj){
    for(int i = 0; i < getVectorSize(); i++){
        for(int j = 0; j < getStringSize(i); j++){
            if(getTile(i, j) == playerChar){
                playerObj.setPosition(i, j);
                return 0;
            }
        }
    }
    std::cout << "No player found on this map.\n";
    return 1;
}

void map::movePlayer(player &playerObj, const int &row, const int &col){
    switch(getTile(row, col)){
    case '.':
        setTile(playerObj.getRowPosition(), playerObj.getColPosition(), emptySpace);
        setTile(row, col, playerChar);
        playerObj.setPosition(row, col);//Registers new player position in player object
        break;
    case '#':
        break;
    default:
        break;
    }
}

void map::moveEnemy(enemy &enemyObj, const int &row, const int &col){
    switch(getTile(row, col)){
    case '.':
        setTile(enemyObj.getRowPosition(), enemyObj.getColPosition(), emptySpace);
        setTile(row, col, enemyObj._symbol);
        enemyObj.setPosition(row, col);//Registers new enemy position in enemy object
        break;
    case '#':
        break;
    default:
        break;
    }
}

int map::getVectorSize() const{
    return vectorSize;
}

int map::getStringSize(const int &index){
    return mapLayout[index].size();
}

int map::getMaxStringSize() const{
    return stringSize;
}

char map::getTile(const int &row, const int &col){
    return mapLayout[row][col];
}

void map::setVectorSize(const int &val){
    vectorSize = val;
}

void map::setMaxStringSize(const int &val){
    stringSize = val;
}

void map::setTile(const int &row, const int &col, const char &newChar){
    mapLayout[row][col] = newChar;
}

