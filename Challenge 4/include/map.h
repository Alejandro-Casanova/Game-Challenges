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
        const char AChar = 'A';
        const char BChar = 'B';

        bool loadMap(std::string fileName);//Loads map from text file
        void printMap() const;//Prints map on the screen.
        bool initEnemies(std::vector<enemy*> &enemyVectorA, std::vector<enemy*> &enemyVectorB);//Initializes all enemies found on the map file
        int checkGrid(); //Checks the grid is initialized correctly

        void moveEnemy(enemy *enemyPointer, const int &row, const int &col, std::vector<enemy*> &enemyVector, std::vector<std::string> &messageVector);//Moves the enemy to selected coordinates (indexed at 0)
        int killEnemy(std::vector<enemy*> &enemyVector, enemy* enemyPtr, std::vector<std::string> &messageVector);//Removes killed enemy and returns xp gained

        int getVectorSize() const{return vectorSize;}//Gets the size of the vector that holds the map layout (map height)
        int getStringSize(const int &index) const{return mapLayout[index].size();} //Gets specific string size
        int getMaxStringSize() const{return stringSize;}//Gets maximum string size (max map width)
        char getTile(const int &row, const int &col) const{return mapLayout[row][col];} //Gets the char at a specific map coordinate (0 indexed)
        enemy* getEnemy(const int &row, const int &col) const{return enemyGrid[row][col];}

    private:
        std::vector <std::string> mapLayout;
        std::vector <std::vector <enemy *> > enemyGrid;

        int stringSize;
        int vectorSize;

        void setVectorSize(const int &val);
        void setMaxStringSize(const int &val);
        void setTile(const int &row, const int &col, const char &newChar); //Sets a particular tile to a char value (coordinates indexed at 0)
        void setGrid(enemy *enemyPointer, const int &row, const int &col);//Sets one tile of the enemy grid

        friend class enemy;
        friend class player;

};

#endif // MAP_H
