#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>

#define WINROW 3 //Number of marks in a row required to win


class Board
{
    public:
        Board(const int &size);

        void printLine() const;//Prints horizontal Line, later used in "printBoard()" function
        void printBoard() const;//Prints actual layout

        void cinIndex(int &input, const int &maxSize, const std::string &message = "",  const int &minSize = 0);//Asks for an int value inside("minSize" , "maxSize"] and stores it in "input"
        bool checkVictory(char mark);//Checks if there are three identical marks in a row (diagonal check only works for 3x3 boards)

        char getTile(int row, int col) const;//Gets the char value of a specific tile
        int getSize() const; //Gets board width
        std::vector<std::vector<char>> getLayout();//Returns the board layout
        void setTile(char mark);//Sets the selected tile with the corresponding mark

    private:
        const int _size;
        std::vector<std::vector<char>> layout;
        const char emptyTile = '.'; //Char used to represent an empty tile
};

#endif // BOARD_H
