#include "player.h"
#include "enemy.h"
#include "map.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <random>
#include <chrono>

void movePlayer(map &mapObj, player &playerObj, std::vector<enemy> &enemyVector, std::vector<std::string> &messageVector, const char &moveChar, bool &moveFlag); //Moves player object on the map according to "moveChar" (atacks if moved towards enemy). Also executes other actions according to "moveChar" (ie print player info)
void moveEnemy(map &mapObj, enemy &enemyObj, const char &moveChar);//Moves enemy object on the map according to "moveChar"
char getRandomMove(); //Returns random character (w, a, s, d)
char getPlayerMove(); //Returns player input

void printScreen(const player &playerObj, const std::vector<enemy> &enemyVector, const map &mapObj, std::vector<std::string> &messageVector);
void printPlayerData(const player &playerObj);
void printGameInfo();

int main()
{
    map map1;
    player player1;
    std::vector<enemy> enemyVector;

    printf("Welcome to TURBO-RPG 2000!\n");

    //Load Map File
    if(map1.loadMap("mapTest.txt") == 1){
        return 1;
    }

    //Initialize player object. Map file must include one '@' character
    if (map1.initPlayer(player1) == 1){
        return 1;
    }

    //Initialize enemies. Map file must include enemie characters
    if (map1.initEnemies(enemyVector) == 1){
        return 1;
    }

    printf("\n");
    system("pause");
    printGameInfo();

    //Game starts
    while(true){
        static std::vector<std::string> messageVector;

        printScreen(player1, enemyVector, map1, messageVector);

        //Checks player death
        if(player1.getHealth() <= 0){
            std::cout << "GAME OVER: YOU HAVE BEEN KILLED\n";
            return 1;
        }

        //Manage player input character
        bool moveFlag = true;
        do{//Repeats while any action other than moving takes place
            if(moveFlag == false){//To prevent screen flashing, only prints map when returning from non-moving input
                printScreen(player1, enemyVector, map1, messageVector);
            }
            //Player moves (or attacks)
            movePlayer(map1, player1, enemyVector, messageVector, getPlayerMove(), moveFlag);
        }while(moveFlag == false);

        //Manage enemy actions in current turn
        for(int i = 0; i < enemyVector.size(); i++){//All enemies move or attack
            if(map1.checkForPlayer(enemyVector[i]) == true){//If an enemy detects the player, it attacks. Otherwise, it moves
                player1.receiveDamage(enemyVector[i].attack(messageVector));
                if(player1.getHealth() <= 0){//If player dies, exit the loop
                    break;
                }
            }else if(enemyVector[i].getSymbol() != 'D'){//Dragon doesn't move
                moveEnemy(map1, enemyVector[i], getRandomMove());
            }
        }
    }


}

void movePlayer(map &mapObj, player &playerObj, std::vector<enemy> &enemyVector, std::vector<std::string> &messageVector, const char &moveChar, bool &moveFlag){
    switch(moveChar){
    case 'w':
    case 'W':
        mapObj.movePlayer(playerObj, enemyVector, messageVector, playerObj.getRowPosition() - 1, playerObj.getColPosition());
        moveFlag = true;
        break;
    case 'a':
    case 'A':
        mapObj.movePlayer(playerObj, enemyVector, messageVector, (playerObj.getRowPosition()), playerObj.getColPosition() - 1);
        moveFlag = true;
        break;
    case 's':
    case 'S':
        mapObj.movePlayer(playerObj, enemyVector, messageVector, (playerObj.getRowPosition() + 1), playerObj.getColPosition());
        moveFlag = true;
        break;
    case 'd':
    case 'D':
        mapObj.movePlayer(playerObj, enemyVector, messageVector, (playerObj.getRowPosition()), playerObj.getColPosition() + 1);
        moveFlag = true;
        break;
    case 'i':
    case 'I':
        printPlayerData(playerObj);
        moveFlag = false;
        break;
    case 'h':
    case 'H':
        printGameInfo();
        moveFlag = false;
        break;
    default:
        moveFlag = true;
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

void printScreen(const player &playerObj, const std::vector<enemy> &enemyVector, const map &mapObj, std::vector<std::string> &messageVector){

    //Print Map
    system("cls");
    mapObj.printMap();

    //Print Health Bar
    printf("Player: %d/%d HP", playerObj.getHealth(), playerObj.getMaxHealth());
    for(int i = 0; i < enemyVector.size(); i++){
        if(mapObj.checkForPlayer(enemyVector[i]) == true){//If an enemy is near the player
            std::cout << " - " << enemyVector[i].getName() << ": " << enemyVector[i].getHealth() << " HP";
        }
    }
    std::cout << std::endl;

    //Print Messages
    for(int i = 0; i < messageVector.size(); i++){
        std::cout << messageVector[i];
    }
    messageVector.clear();
}

void printPlayerData(const player &playerObj){
    system("cls");
    printf("Level: %d \nCurrent XP: %d/%d\n", playerObj.getLevel(), playerObj.getXp(), playerObj.getMaxXp());
    printf("Health: %d/%d HP\n", playerObj.getHealth(), playerObj.getMaxHealth());
    printf("Attack: %d \nDefence: %d \nPrecision: %.2f %\n", playerObj.getAttack(), playerObj.getDefence(), 100*playerObj.getPrecision());

    std::cout << std::endl;
    system("pause");
}

void printGameInfo(){
    system("cls");
    printf("Game Controls:\n\nH: Press anytime to display this information.\n");
    printf("I: Press anytime to display player information.\n");
    printf("W,A,S,D: Press to move your player, move against enemies to attack!\n");

    printf("\nPressing any other key during the game will bring forward the next turn, \nplayer won't move but enemies will!\n\n");
    system("pause");
}
