#ifndef MAP_H
#define MAP_H

#include "player.h"
#include "enemy.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

class map
{
    public:
        map();
        const char playerChar = '@';
        const char emptySpace = '.';
        const char zombieChar = 'Z';
        const char skeletonChar = 'S';
        const char dragonChar = 'D';

        bool loadMap(std::string fileName);//Loads map from text file
        void printMap() const;//Prints map on the screen.
        bool initPlayer(player &playerObj); //Initializes player object's position. map file must include one '@'
        enemy newEnemy(const std::string &name, const char &symbol, const int &rowVal, const int &colVal);//Returns new and initialized enemy object
        bool initEnemies(std::vector<enemy> &enemyVector);//Initializes all enemies found on the map file

        void movePlayer(player &playerObj, std::vector<enemy> &enemyVector, std::vector<std::string> &messageVector, const int &row, const int &col);//Moves the player to selected coordinates (indexed at 0) and attacks if tile is occupied by enemy
        void moveEnemy(enemy &enemyObj, const int &row, const int &col);//Moves the enemy to selected coordinates (indexed at 0)
        bool checkForPlayer(const enemy &enemyObj) const; //Checks surroundings of enemy for player presence (doesn't check diagonals)
        int killEnemy(std::vector<enemy> &enemyVector, const int &index, std::vector<std::string> &messageVector);//Removes killed enemy and returns xp gained
        int getVectorSize() const;//Gets the size of the vector that holds the map layout (map height)
        int getStringSize(const int &index) const; //Gets specific string size
        int getMaxStringSize() const;//Gets maximum string size (max map width)
        char getTile(const int &row, const int &col) const; //Gets the char at a specific map coordinate (0 indexed)

    private:
        std::vector<std::string> mapLayout;
        int stringSize;
        int vectorSize;

        void setVectorSize(const int &val);
        void setMaxStringSize(const int &val);
        void setTile(const int &row, const int &col, const char &newChar); //Sets a particular tile to a char value (coordinates indexed at 0)

        friend class enemy;
        friend class player;

};

#endif // MAP_H
