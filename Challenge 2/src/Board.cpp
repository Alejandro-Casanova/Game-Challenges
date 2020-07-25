#include "Board.h"

Board::Board()//Makes a blank board
{
    for (int i = 0; i < SIZEY; i++){
        for(int j = 0; j < SIZEX; j++){
            layout[i][j] = emptyTile;
        }
    }
}

void Board::cinIndex(int &input, const int &maxSize, const std::string &message){
    std::cout << message;
    while(true){
        while(!(std::cin >> input)){
            std::cout << "Invalid input, please try again with a single number: ";
            std::cin.clear();
            std::cin.ignore(999, '\n');
        }
        //Checks if the value is correct
        if(!((input > 0)&&(input<=maxSize))){
            std::cout << "Please introduce a valid number: ";
        }
        else{
            break;
        }
    }
}

void Board::printLine() const{//Prints a horizontal line, used in "Board::printBoard()" to print lines between rows
    std::cout<<std::endl;
    std::cout<<"--";
    for(int i = 0; i < SIZEX; i++){
        std::cout<<"----";
    }
    std::cout<<std::endl;
}

void Board::printBoard() const{//Prints current layout
    system("cls");
    std::cout<<"**TIC TAC TOE**";
    //Print row of x indexes
    std::cout<<"\n |";
    for(int i = 1; i <= SIZEX; i++){
        std::cout<<" "<<i<<" |";
    }
    printLine();
    for(int i = 0; i < SIZEY; i++){
        std::cout<<i+1<<"|";
        for(int j = 0; j < SIZEX; j++){
            std::cout<<" "<<layout[i][j]<<" |";
        }
        printLine();
    }
}

void Board::setTile(char mark){
    int row, col;
    bool freeTile = false; //Indicates if the selected tile is free or already ocuppied
    do{
        cinIndex(row, SIZEY, "Indicate desired row number: ");
        cinIndex(col, SIZEX, "Indicate desired colum number: ");

        if(!((getTile(row, col)) == emptyTile)){//Checks if the indicated tile is taken
            freeTile = false;
            std::cout<<"The tile selected is already taken, please try again.\n";
            system("Pause");
            system("cls");
            printBoard();
        }
        else {
            freeTile = true;
        }

    }while(freeTile==false);
    layout[row-1][col-1] = mark; //Takes place if the tile was free
}

char Board::getTile(int row, int col) const{
    return layout[row-1][col-1];
}

void Board::getLayout(char array[SIZEY][SIZEX]){
    for(int i = 0; i < SIZEY; i++){
        for(int j = 0; j < SIZEX; j++){
            array[i][j] = layout[i][j];
        }
    }
}

bool Board::checkVictory(char mark){
    char layout[SIZEY][SIZEX];
    int auxFlag = 0, auxFlag2 = 0;
    getLayout(layout);

    //Check rows
    for(int i = 0; i < SIZEY; i++){
        auxFlag = 0;
        for(int j = 0; j < SIZEX; j++){
            if(getTile(i + 1, j + 1) == mark){
                auxFlag++;
            }
        }
        if(auxFlag>=WINROW){
            return true;
        }
    }

    //Check colums
    for(int i = 0; i < SIZEX; i++){
        auxFlag = 0;
        for(int j = 0; j < SIZEY; j++){
            if(getTile(j + 1, i + 1) == mark){
                auxFlag++;
            }
        }
        if(auxFlag>=WINROW){
            return true;
        }
    }

    //Check diagonals (Only works for 3x3 layout, as it only chacks the main 2 diagonals)
    auxFlag = 0;
    for(int i = 0; i < std::min(SIZEX, SIZEY); i++){
        if(getTile(i + 1, i + 1) == mark){ //Checks main diagonal (11,22,33)
            auxFlag++;
        }
        if(getTile(i + 1, 3 - i) == mark){ //Checks opposite diagonal (13,22,31)
            auxFlag2++;
        }
    }
    if((auxFlag == WINROW)||(auxFlag2 == WINROW)){
        return true;
    }
    return false;
}

