#include "Board.h"

//Board::Board(const int &size) : _size(size)//Makes a blank board
//{
//    layout.resize(size, std::vector<char>(size, emptyTile));
//}

//Initialization of member variables
int Board::_size = 0;
std::vector<std::vector<char>> Board::layout = std::vector<std::vector<char>>(0, std::vector<char>(0, emptyTile));

//Function definitions
void Board::cinIndex(int &input, const int &maxSize, const std::string &message, const int &minSize){
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

void Board::printLine(){//Prints a horizontal line, used in "Board::printBoard()" to print lines between rows
    std::cout<<std::endl;
    std::cout<<"---";
    for(int i = 0; i < getSize(); i++){
        std::cout<<"----";
        if(i >= 9){
            std::cout << "-";
        }
    }
    std::cout<<std::endl;
}

void Board::printBoard(){//Prints current layout
    system("cls");
    std::cout<<"**TIC TAC TOE**";

    //Print row of x indexes
    std::cout<<"\n  |";
    for(int i = 1; i <= getSize(); i++){
        std::cout<<" "<<i<<" |";
    }
    printLine();

    for(int i = 0; i < getSize(); i++){
        if(i < 9){
            std::cout << " ";
        }
        std::cout<<i+1<<"|";
        for(int j = 0; j < getSize(); j++){
            if(j >= 9){
                std::cout << " ";
            }
            std::cout<<" "<<layout[i][j]<<" |";

        }
        printLine();
    }
}

void Board::askForMove(char mark){
    int row, col;
    bool freeTile = false; //Indicates if the selected tile is free or already ocuppied
    do{
        cinIndex(row, getSize(), "Indicate desired row number: ");
        cinIndex(col, getSize(), "Indicate desired colum number: ");

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
    setTile(row - 1, col - 1, mark); //Takes place if the tile was free
}

void Board::setTile(const int &row, const int &col, const char &mark){
    layout[row][col] = mark;
}

char Board::getTile(int row, int col){
    return layout[row-1][col-1];
}

std::vector<std::vector<char>> Board::getLayout(){
    return layout;
}

int Board::getSize(){
    return _size;
}

bool Board::checkVictory(char mark){
    int auxFlag = 0;

    //Check rows
    for(int i = 0; i < getSize(); i++){
        auxFlag = 0;
        for(int j = 0; j < getSize(); j++){
            if(getTile(i + 1, j + 1) == mark){
                auxFlag++;
            }else {
                auxFlag = 0;
            }
            if(auxFlag>=WINROW){
                return true;
            }
        }

    }

    //Check colums
    for(int i = 0; i < getSize(); i++){
        auxFlag = 0;
        for(int j = 0; j < getSize(); j++){
            if(getTile(j + 1, i + 1) == mark){
                auxFlag++;
            }else{
                auxFlag = 0;
            }
            if(auxFlag>=WINROW){
                return true;
            }
        }

    }

    //Check descending diagonals, i.e. {(1,1),(2,2),(3,3)}
    int k = 0;
    for(int i = (getSize() - WINROW + 1); i > 0; i--){
        auxFlag = 0;
        for(int j = 0; j < (3 + k); j++){
            if(getTile(i + j, j + 1) == mark){
                auxFlag++;
            }else{
                auxFlag = 0;
            }
            if(auxFlag >= WINROW){
                return true;
            }
        }
        k++;
    }
    k = 0;
    //Checks descending diagonals after the main diagonal
    for(int i = 2; i < getSize() - 1; i++){
        auxFlag = 0;
        for(int j = 0; j < getSize() - k; j++){
            if(getTile(j + 1, i + j) == mark){
                auxFlag++;
            }else{
                auxFlag = 0;
            }
            if(auxFlag >= WINROW){
                return true;
            }
        }
        k++;
    }
    //Checks for ascending diagonals, i.e. {(3,1),(2,2),(1,3)}
    k = 0;
    for(int i = (getSize()); i >= WINROW; i--){
        auxFlag = 0;
        for(int j = 0; j < (getSize() - k); j++){
            if(getTile(i - j, j + 1) == mark){
                auxFlag++;
            }else{
                auxFlag = 0;
            }
            if(auxFlag >= WINROW){
                return true;
            }
        }
        k++;
    }
    k = 0;
    //Checks ascending diagonals after the main diagonal
    for(int i = 2; i < getSize() - 1; i++){
        auxFlag = 0;
        for(int j = 0; j < getSize() - k; j++){
            if(getTile(getSize()-j, i + j) == mark){
                auxFlag++;
            }else{
                auxFlag = 0;
            }
            if(auxFlag >= WINROW){
                return true;
            }
        }
        k++;
    }
    return false;
}

void Board::setSize(const int &newSize){
    _size = newSize;
}

void Board::resizeBoard(const int &newSize){
    layout.resize(newSize, std::vector<char>(newSize, emptyTile));
    setSize(newSize);
}

void Board::clearBoard(){
    layout.assign(_size, std::vector<char>(_size, emptyTile));
}
