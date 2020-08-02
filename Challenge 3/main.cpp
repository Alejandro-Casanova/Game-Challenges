#include "player.h"
#include "enemy.h"
#include "map.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <random>
#include <chrono>

void getPlayerMove(map &mapObj, player &playerObj);
char getRandomMove();

int main()
{
    std::cout << getRandomMove() << getRandomMove();
    system("pause");
    map map1;
    player player1;
    map1.loadMap("mapTest.txt");
    map1.printMap();

    if (map1.initPlayer(player1) == 1){//Initialize player object. Map file must include one '@' character
        return 1;
    };

    while(true){
        map1.printMap();
        getPlayerMove(map1, player1);


    }
}

void getPlayerMove(map &mapObj, player &playerObj){
    char input;
    input = _getch();
    switch(input){
    case 'w':
    case 'W':
        mapObj.movePlayer(playerObj, playerObj.getRowPosition() - 1, playerObj.getColPosition());
        break;
    case 'a':
    case 'A':
        mapObj.movePlayer(playerObj, (playerObj.getRowPosition()), playerObj.getColPosition() - 1);
        break;
    case 's':
    case 'S':
        mapObj.movePlayer(playerObj, (playerObj.getRowPosition() + 1), playerObj.getColPosition());
        break;
    case 'd':
    case 'D':
        mapObj.movePlayer(playerObj, (playerObj.getRowPosition()), playerObj.getColPosition() + 1);
        break;
    default:
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
