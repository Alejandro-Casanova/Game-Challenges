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
    printf("Map Loaded Succesfully:\n\n");
    printMap();
    printf("\n");
    return 0;
}

void map::printMap() const{
    for(int i = 0; i < getVectorSize(); i++){
        std::cout << mapLayout[i] << std::endl;
    }
}

bool map::initPlayer(player &playerObj){
    for(int i = 0; i < getVectorSize(); i++){
        for(int j = 0; j < getStringSize(i); j++){
            if(getTile(i, j) == playerChar){
                playerObj.setPosition(i, j);
                printf("Player Initialized Succesfully.\n");
                return 0;
            }
        }
    }
    std::cout << "No player found on this map.\n";
    return 1;
}

bool map::initEnemies(std::vector<enemy> &enemyVector){
    int enemyCounter = 0;

    //Scans for enemies
    for(int i = 0; i < getVectorSize(); i++){
        for(int j = 0; j < getStringSize(i); j++){

            //Initializes Zombie
            if(getTile(i, j) == zombieChar){
                std::stringstream nameBuffer;
                static int zombieCounter = 0;

                nameBuffer << "Zombie " << (zombieCounter + 1);
                enemyVector.push_back(newEnemy(nameBuffer.str(), zombieChar, i, j));
                enemyCounter++;
                zombieCounter++;
            }
            //Initializes Skeleton
            if(getTile(i, j) == skeletonChar){
                std::stringstream nameBuffer;
                static int skeletonCounter = 0;

                nameBuffer << "Skeleton " << (skeletonCounter + 1);
                enemyVector.push_back(newEnemy(nameBuffer.str(), skeletonChar, i, j));
                enemyCounter++;
                skeletonCounter++;
            }
            //Initializes Dragon
            if(getTile(i, j) == dragonChar){
                std::stringstream nameBuffer;
                static int dragonCounter = 0;

                nameBuffer << "Dragon " << (dragonCounter + 1);
                enemyVector.push_back(newEnemy(nameBuffer.str(), dragonChar, i, j));
                enemyCounter++;
                dragonCounter++;
            }
        }
    }
    if(enemyCounter == 0){
        std::cout << "No enemies found on this map.\n";
        return 1;
    }else{
        std::cout << "Found " << enemyCounter << " enemies on this map.\n";
        return 0;
    }
}

enemy map::newEnemy(const std::string &name, const char &symbol, const int &rowVal, const int &colVal){
    enemy enemyObj(name, symbol, rowVal, colVal);
    return enemyObj;
}

void map::movePlayer(player &playerObj, std::vector<enemy> &enemyVector, std::vector<std::string> &messageVector, const int &row, const int &col){
    switch(getTile(row, col)){
    case '.':
        setTile(playerObj.getRowPosition(), playerObj.getColPosition(), emptySpace);
        setTile(row, col, playerChar);
        playerObj.setPosition(row, col);//Registers new player position in player object
        break;
    case '#':
        break;
    case 'Z':{
    case 'S':
    case 'D':
        bool attackFlag = false;//For security, checks attack has been succesful
        for(int i = 0; i < enemyVector.size(); i++){//Checks which enemy is being attacked
            if((enemyVector[i].getRowPosition() == row) && (enemyVector[i].getColPosition() == col)){
                std::string attackMessage;
                enemyVector[i].receiveDamage(playerObj.attack(attackMessage));
                messageVector.push_back(attackMessage);
                if(enemyVector[i].getHealth() <=0){
                    playerObj.gainXp(killEnemy(enemyVector, i, messageVector), messageVector);
                }
                attackFlag = true;
            }
        }
        assert(attackFlag = true);
        break;
    }
    default:
        assert(true == false);
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

bool map::checkForPlayer(const enemy &enemyObj) const{
    int row = enemyObj.getRowPosition();
    int col = enemyObj.getColPosition();

    if(getTile(row - 1, col) == '@') return true;
    if(getTile(row + 1, col) == '@') return true;
    if(getTile(row, col - 1) == '@') return true;
    if(getTile(row, col + 1) == '@') return true;
    return false;
}

int map::killEnemy(std::vector<enemy> &enemyVector, const int &index, std::vector<std::string> &messageVector){
    int row, col, xp;
    std::stringstream message;

    row = enemyVector[index].getRowPosition();
    col = enemyVector[index].getColPosition();
    xp = enemyVector[index].getXp();

    message << "You killed " << enemyVector[index].getName() << "!\n" << "You gained " << xp << " experience points.\n";
    enemyVector.erase(enemyVector.begin() + index);
    setTile(row, col, emptySpace);
    messageVector.push_back(message.str());
    return xp;

}


int map::getVectorSize() const{
    return vectorSize;
}

int map::getStringSize(const int &index) const{
    return mapLayout[index].size();
}

int map::getMaxStringSize() const{
    return stringSize;
}

char map::getTile(const int &row, const int &col) const{
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

