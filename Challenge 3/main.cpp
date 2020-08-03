#include "player.h"
#include "enemy.h"
#include "map.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <random>
#include <chrono>

void movePlayer(map &mapObj, player &playerObj, std::vector<enemy> &enemyVector, std::vector<std::string> &messageVector, const char &moveChar); //Moves player object on the map according to "moveChar" (atacks if moved towards enemy)
void moveEnemy(map &mapObj, enemy &enemyObj, const char &moveChar);//Moves enemy object on the map according to "moveChar"
char getRandomMove(); //Returns random character (w, a, s, d)
char getPlayerMove(); //Returns player input (w, a, s, d)

void printScreen(const player &playerObj, const std::vector<enemy> &enemyVector, const map &mapObj, std::vector<std::string> &messageVector);

int main()
{
    map map1;
    player player1;
    std::vector<enemy> enemyVector;
    map1.loadMap("mapTest.txt");
    map1.printMap();

    if (map1.initPlayer(player1) == 1){//Initialize player object. Map file must include one '@' character
        return 1;
    };

    if (map1.initEnemies(enemyVector) == 1){//Initialize enemies. Map file must include enemies
        return 1;
    };

    system("pause");
    system("cls");
    map1.printMap();


    while(player1.getHealth() > 0){//Game starts
        std::string attackMessage;
        static std::vector<std::string> messageVector;

        printScreen(player1, enemyVector, map1, messageVector);
        movePlayer(map1, player1, enemyVector, messageVector, getPlayerMove());//First, the player moves (or attacks)

        for(int i = 0; i < enemyVector.size(); i++){//All enemies move or attack
            if(map1.checkForPlayer(enemyVector[i]) == true){//If an enemy detects the player
                player1.receiveDamage(enemyVector[i].attack(attackMessage));
                messageVector.push_back(attackMessage);
                if(player1.getHealth() <= 0){
                    std::cout << "YOU HAVE BEEN KILLED: GAME OVER\n";
                    return 1;
                }
            }else{
                moveEnemy(map1, enemyVector[i], getRandomMove());
            }
        }
    }

}

void movePlayer(map &mapObj, player &playerObj, std::vector<enemy> &enemyVector, std::vector<std::string> &messageVector, const char &moveChar){
    switch(moveChar){
    case 'w':
    case 'W':
        mapObj.movePlayer(playerObj, enemyVector, messageVector, playerObj.getRowPosition() - 1, playerObj.getColPosition());
        break;
    case 'a':
    case 'A':
        mapObj.movePlayer(playerObj, enemyVector, messageVector, (playerObj.getRowPosition()), playerObj.getColPosition() - 1);
        break;
    case 's':
    case 'S':
        mapObj.movePlayer(playerObj, enemyVector, messageVector, (playerObj.getRowPosition() + 1), playerObj.getColPosition());
        break;
    case 'd':
    case 'D':
        mapObj.movePlayer(playerObj, enemyVector, messageVector, (playerObj.getRowPosition()), playerObj.getColPosition() + 1);
        break;
    default:
        break;
    }
}

void moveEnemy(map &mapObj, enemy &enemyObj, const char &moveChar){
    switch(moveChar){
    case 'w':
    case 'W':
        mapObj.moveEnemy(enemyObj, enemyObj.getRowPosition() - 1, enemyObj.getColPosition());
        break;
    case 'a':
    case 'A':
        mapObj.moveEnemy(enemyObj, (enemyObj.getRowPosition()), enemyObj.getColPosition() - 1);
        break;
    case 's':
    case 'S':
        mapObj.moveEnemy(enemyObj, (enemyObj.getRowPosition() + 1), enemyObj.getColPosition());
        break;
    case 'd':
    case 'D':
        mapObj.moveEnemy(enemyObj, (enemyObj.getRowPosition()), enemyObj.getColPosition() + 1);
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

void printScreen(const player &playerObj, const std::vector<enemy> &enemyVector, const map &mapObj, std::vector<std::string> &messageVector){

    //Print Map
    system("cls");
    mapObj.printMap();

    //Print Health Bar
    std::cout << "Player: " << playerObj.getHealth() << " HP";
    for(int i = 0; i < enemyVector.size(); i++){
        if(mapObj.checkForPlayer(enemyVector[i]) == true){//If an enemy is near the player
            std::cout << " - " << enemyVector[i].getName() << ": " << enemyVector[i].getHealth() << " HP";
        }
    }
    std::cout << std::endl;

    //Print enemy Messages
    for(int i = 0; i < messageVector.size(); i++){
        std::cout << messageVector[i];
    }
    messageVector.clear();
}
