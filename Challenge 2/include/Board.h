#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

#define SIZEX 3 //Number of colums
#define SIZEY 3 //Number of rows
#define WINROW 3 //Number of marks in a row required to win


class Board
{
    public:
        Board();

        void printLine() const;//Prints horizontal Line, later used in "printBoard()" function
        void printBoard() const;//Prints actual layout

        void cinIndex(int &var, int maxSize);//Asks for an int value inside(0 , "maxSize"] and stores it in "var"
        bool checkVictory(char mark);//Checks if there are three identical marks in a row (diagonal check only works for 3x3 boards)

        char getTile(int row, int col) const;//Gets the char value of a specific tile
        void getLayout(char [SIZEY][SIZEX]);//Makes a copy of the board layout
        void setTile(char mark);//Sets the selected tile with the corresponding mark

    private:
        char layout[SIZEX][SIZEY];
        const char emptyTile = '.'; //Char used to represent an empty tile
};

#endif // BOARD_H
