#ifndef MAP_H
#define MAP_H

#include "player.h"
#include "enemy.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class map
{
    public:
        map();
        const char playerChar = '@';
        const char emptySpace = '.';

        bool loadMap(std::string fileName);
        void printMap() const;
        bool initPlayer(player &playerObj); //Initializes player object's position.

        void movePlayer(player &playerObj, const int &row, const int &col);//Moves the player to selected coordinates (indexed at 0)
        void moveEnemy(enemy &enemyObj, const int &row, const int &col);

        int getVectorSize() const;
        int getStringSize(const int &index); //Gets specific string size
        int getMaxStringSize() const;
        char getTile(const int &row, const int &col); //Gets the char at a specific map coordinate (0 indexed)

    private:
        std::vector<std::string> mapLayout;
        int stringSize;
        int vectorSize;

        void setVectorSize(const int &val);
        void setMaxStringSize(const int &val);
        void setTile(const int &row, const int &col, const char &newChar); //Sets a particular tile to a char value (coordinates indexed at 0)


};

#endif // MAP_H
