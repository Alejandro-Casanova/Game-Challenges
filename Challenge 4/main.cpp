#include "player.h"
#include "enemy.h"
#include "map.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <random>
#include <chrono>
#include <algorithm>


void moveEnemy(map &mapObj, enemy *enemyPointer, const char &moveChar, std::vector<enemy*> &otherEnemyVector, std::vector<std::string> &messageVector);//Moves enemy object on the map according to "moveChar". Prevents running into walls and attacks enemies encountered. Also controls enemy deaths.
char getRandomMove(); //Returns random character (w, a, s, d)
char getPlayerMove(); //Returns player input
void shuffleVector(std::vector<enemy*> &enemyVector);//Shuffles enemy vector to improve randomness

void printScreen(const map &mapObj, std::vector<std::string> &messageVector);
//void printGameInfo();

int main()
{
    map map1;
    std::vector<enemy*> enemyVectorA, enemyVectorB;

    printf("Welcome to 2D Battle Simulator!\n");

    //Load Map File
    if(map1.loadMap("mapTest.txt") == 1){
        return 1;
    }

    //Initialize enemies. Map file must include enemie characters
    if (map1.initEnemies(enemyVectorA, enemyVectorB) == 1){
        return 1;
    }

    //Shuffle enemy vectors to improve randomness and prevent army movement patterns.
    shuffleVector(enemyVectorA);
    shuffleVector(enemyVectorB);

    //Check grid initialization
    if(map1.checkGrid() == 0){
        std::cout << "Grid checked succesfully\n";
    }

    _getch();

    //Game starts
    while(true){
        static std::vector<std::string> messageVector;
        printScreen(map1, messageVector);

        //Checks for Victory
        if(enemyVectorA.size() <= 0){
            std::cout << "GAME OVER: Army B Won!\n";
            return 1;
        }else if(enemyVectorB.size() <= 0){
            std::cout << "GAME OVER: Army A Won!\n";
            return 1;
        }

        char wait;
        wait = _getch();

        //Manage enemy actions in current turn
        for(int i = 0; i < std::max(enemyVectorA.size(), enemyVectorB.size()); i++){//All enemies move or attack
            if(i < enemyVectorA.size()){
                moveEnemy(map1, enemyVectorA[i], enemyVectorA[i]->getMove(enemyVectorA[i]->findEnemy(enemyVectorB)), enemyVectorB, messageVector);
            }
            if(i < enemyVectorB.size()){
                moveEnemy(map1, enemyVectorB[i], enemyVectorB[i]->getMove(enemyVectorB[i]->findEnemy(enemyVectorA)), enemyVectorA, messageVector);
            }
            if((enemyVectorA.size() == 0) || (enemyVectorB.size() == 0)){
                break;
            }
        }

    }


}

void moveEnemy(map &mapObj, enemy *enemyPointer, const char &moveChar, std::vector<enemy*> &otherEnemyVector, std::vector<std::string> &messageVector){
    int row = enemyPointer->getRowPosition();
    int col = enemyPointer->getColPosition();

    switch(moveChar){
    case 'w':
    case 'W':
        mapObj.moveEnemy(enemyPointer, row - 1, col, otherEnemyVector, messageVector);
        break;
    case 'a':
    case 'A':
        mapObj.moveEnemy(enemyPointer, row, col - 1, otherEnemyVector, messageVector);
        break;
    case 's':
    case 'S':
        mapObj.moveEnemy(enemyPointer, row + 1, col,  otherEnemyVector, messageVector);
        break;
    case 'd':
    case 'D':
        mapObj.moveEnemy(enemyPointer, row, col + 1,  otherEnemyVector, messageVector);
        break;
    default:
        break;
    }
}

char getPlayerMove(){
    char input;
    input = _getch();
    switch(input){
    case 'w':
    case 'W':
        return 'w';
        break;
    case 'a':
    case 'A':
        return 'a';
        break;
    case 's':
    case 'S':
        return 's';
        break;
    case 'd':
    case 'D':
        return 'd';
        break;
    case 'i':
    case 'I':
        return 'i';
        break;
    case 'h':
    case 'H':
        return 'h';
        break;
    default:
        return '0';
        break;
    }
}

char getRandomMove(){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count(); //Generate Seed from absolute time
    static std::default_random_engine eng(seed); //Create random engine object
    std::uniform_int_distribution<int> intDist(0, 7); //Create uniform integer distribution object

    switch(intDist(eng)){
    case 0:
        return 'w';
        break;
    case 1:
        return 'a';
        break;
    case 2:
        return 's';
        break;
    case 3:
        return 'd';
        break;
    default:
        return '0';
        break;
    }
}

void shuffleVector(std::vector<enemy*> &enemyVector){
    static std::default_random_engine eng{std::random_device{}()}; //Create random engine object

    for(int i = enemyVector.size() - 1; i > 0; i--){
        std::uniform_int_distribution<int> intDist(0, i - 1); //Create uniform real distribution object
        int swapVal = intDist(eng);
        enemy* swapBuffer = enemyVector[i];

        enemyVector[i] = enemyVector[swapVal];
        enemyVector[swapVal] = swapBuffer;
    }
}

void printScreen(const map &mapObj, std::vector<std::string> &messageVector){

    //Print Map
    system("cls");
    printf("Welcome to 2D Battle Simulator!\n\n\n");
    mapObj.printMap();

    //Print Messages
    for(int i = 0; i < messageVector.size(); i++){
        std::cout << messageVector[i];
    }
    messageVector.clear();
}

//void printGameInfo(){
//    system("cls");
//    printf("Game Controls:\n\nH: Press anytime to display this information.\n");
//    printf("I: Press anytime to display player information.\n");
//    printf("W,A,S,D: Press to move your player, move against enemies to attack!\n");
//
//    printf("\nPressing any other key during the game will bring forward the next turn, \nplayer won't move but enemies will!\n\n");
//    system("pause");
//}
