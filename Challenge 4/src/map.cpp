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

bool map::initEnemies(std::vector<enemy*> &enemyVectorA, std::vector<enemy*> &enemyVectorB){
    int enemyCounter = 0;

    //Scans for enemies
    for(int i = 0; i < getVectorSize(); i++){

        std::vector <enemy*> auxVector(0);

        for(int j = 0; j < getStringSize(i); j++){

            //Initializes A Army
            if(getTile(i, j) == AChar){
                std::stringstream nameBuffer;
                static int ACounter = 0;

                nameBuffer << "A-Soldier " << (ACounter + 1);
                enemyVectorA.push_back(new enemy(nameBuffer.str(), AChar, i, j));

                auxVector.push_back(enemyVectorA[ACounter]);

                enemyCounter++;
                ACounter++;
            }

            //Initializes B Army
            else if(getTile(i, j) == BChar){
                std::stringstream nameBuffer;
                static int BCounter = 0;

                nameBuffer << "B-Soldier " << (BCounter + 1);
                enemyVectorB.push_back(new enemy(nameBuffer.str(), BChar, i, j));

                auxVector.push_back(enemyVectorB[BCounter]);

                enemyCounter++;
                BCounter++;
            }
            else{
                auxVector.push_back(nullptr);
            }
        }
        enemyGrid.push_back(auxVector);
    }
    if(enemyCounter == 0){
        std::cout << "No enemies found on this map.\n";
        return 1;
    }else{
        std::cout << "Found " << enemyCounter << " enemies on this map.\n";
        return 0;
    }
}

int map::checkGrid(){
    for(int i = 0; i < getVectorSize(); i++){
        for(int j = 0; j < getStringSize(i); j++){
            switch(getTile(i, j)){
            case '.':
            case '#':
                assert(enemyGrid[i][j] == nullptr);
                break;
            case 'A':{
            case 'B':
                enemy *enemyptr = enemyGrid[i][j];
                int row = enemyptr->getRowPosition();
                int col = enemyptr->getColPosition();
                assert((row == i) && (col == j));
                break;
            }
            default:
                assert(false);
                break;
            }
        }
    }
    return 0;
}

void map::moveEnemy(enemy *enemyPointer, const int &row, const int &col, std::vector<enemy*> &enemyVector, std::vector<std::string> &messageVector){
    int prevRow = enemyPointer->getRowPosition();
    int prevCol = enemyPointer->getColPosition();
    char myChar = enemyPointer->getSymbol();

    switch(getTile(row, col)){
    case '.':
        //Removes enemy from previous tile
        setTile(prevRow, prevCol, emptySpace);
        setGrid(nullptr, prevRow, prevCol);

        //Sets enemy on new tile
        setTile(row, col, enemyPointer->_symbol);
        enemyPointer->setPosition(row, col);//Registers new enemy position in enemy object
        setGrid(enemyPointer, row, col);
        break;
    case '#':
        break;
    case 'A':{
        enemy *enemyPtr = nullptr;//Saves pointer to "enemy under attack" (enemyPtr != enemyPointer)
        if(myChar == 'A'){
            break;
        }else{
            enemyPtr = getEnemy(row, col);
            enemyPtr->receiveDamage(enemyPointer->attack());
            if(enemyPtr->getHealth() <= 0){
                killEnemy(enemyVector, enemyPtr, messageVector);
            }
        }
        break;
    }
    case 'B':{
        enemy *enemyPtr = nullptr;
        if(myChar == 'B'){
            break;
        }else{
            enemyPtr = getEnemy(row, col);
            enemyPtr->receiveDamage(enemyPointer->attack());
            if(enemyPtr->getHealth() <= 0){
                killEnemy(enemyVector, enemyPtr, messageVector);
            }
        }
        break;
    }
    default:
        break;
    }
}

int map::killEnemy(std::vector<enemy*> &enemyVector, enemy* enemyPtr, std::vector<std::string> &messageVector){
    int row, col, xp;
    std::stringstream message;

    row = enemyPtr->getRowPosition();
    col = enemyPtr->getColPosition();

    message << "Death: " << enemyPtr->getName() << std::endl;

    //Look for pointer and delete it
    for(int i = 0; i < enemyVector.size(); i++){
        if(enemyVector[i] == enemyPtr){
            enemyVector.erase(enemyVector.begin() + i);
            break;
        }
    }
    //Free space
    delete enemyPtr;

    //Remove enemy from map
    setTile(row, col, emptySpace);
    setGrid(nullptr, row, col);

    messageVector.push_back(message.str());
    return 0;

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

void map::setGrid(enemy *enemyPointer, const int &row, const int &col){
    enemyGrid[row][col] = enemyPointer;
}

