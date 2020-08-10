#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>

#define WINROW 3 //Number of marks in a row required to win

const char emptyTile = '.'; //Char used to represent an empty tile

class Board
{
    public:
        Board(const int &size);

        static void printLine();//Prints horizontal Line, later used in "printBoard()" function
        static void printBoard();//Prints actual layout

        static void cinIndex(int &input, const int &maxSize, const std::string &message = "",  const int &minSize = 0);//Asks for an int value inside("minSize" , "maxSize"] and stores it in "input"
        static void askForMove(char mark);//Sets the selected tile with the corresponding mark
        static bool checkVictory(char mark);//Checks if there are three identical marks in a row (diagonal check only works for 3x3 boards)

        static char getTile(int row, int col);//Gets the char value of a specific tile (indexed at 1)
        static int getSize(); //Gets board width
        static std::vector<std::vector<char>> getLayout();//Returns the board layout
        static void setTile(const int &row, const int &col, const char &mark);//Indexed at 0
        static void setSize(const int &newSize);
        static void resizeBoard(const int &newSize);
        static void clearBoard();


    private:
        static int _size;
        static std::vector<std::vector<char>> layout;

};

#endif // BOARD_H
