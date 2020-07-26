#include <iostream>
#include <string>
#include <vector>

#include "Player.h"
#include "Board.h"

#define MAXBOARDSIZE 15
#define MINBOARDSIZE 3

Player setPlayer(int playerNumber); //Sets players 1 and 2 from user input
void cinCheckChar(std::string &input, const std::string &message);//Asks for a single character input
bool switchAsk();//Returns true if 'Y' is typed in and false if 'N' is typed in.
void cinCheckInt(int &input, const int &maxSize, const int &minSize, const std::string &message = "");

int main()
{
    int boardSize = 0;
    std::vector<Player> player;//Player vector created
    std::cout << "Hello! Welcome to tic-tac-toe!\n";

    //Set Board
    cinCheckInt(boardSize, MAXBOARDSIZE, MINBOARDSIZE, "Indicate desired board width (between 3 and 15): ");
    Board board(boardSize);//Board object created

    //Set Players
    player.push_back(setPlayer(1));
    player.push_back(setPlayer(2));
    std::cout << "\nDo you wish to add a third player? (Not recommended for boards <5x5) (Y/N): ";
    if(switchAsk() == true){//Set third player
            player.push_back(setPlayer(3));
    }
    std::cout<<"\nThe Game Is Ready!\n";
    system("Pause");

    //Game Starts
    board.printBoard();
    boardSize = board.getSize();
    int turn = 0;
    for(int i = 0; i < boardSize*boardSize; i++){//The game keeps on until the board is full or any player wins
        std::cout<<player[turn].getName()<<"! It's your turn!\n";
        board.setTile(player[turn].getMark());
        board.printBoard();

        //Checks for win flag
        player[turn].setWinFlag(board.checkVictory(player[turn].getMark()));
        if((player[turn].getWinFlag() == true)){//If any player wins before the board is full, the loop is interrupted
            break;
        }

        //Next player's turn
        switch (turn){
        case 2:
            turn = 0;
            break;
        case 1:
            if(player.size() == 2){
                turn--;
                break;
            }
        case 0:
            turn++;
        }
    }

    //Results are printed
    std::cout<<"The Game is Over! Result: ";
    if(player[turn].getWinFlag() == true){
        std::cout<<player[turn].getName()<<" wins!";
    }
    else{
        std::cout<<"Ties!";
    }


}

Player setPlayer(int playerNumber){
    std::string inputName, mark;
    std::cout<<"\nPlayer "<<playerNumber<<", please enter your name: ";
    getline(std::cin, inputName); //Get player name
    cinCheckChar(mark, "Now enter the symbol you want to play with: "); //Get single caracter
    Player player(inputName, mark.front());
    return player;
}

void cinCheckChar(std::string &input, const std::string &message){
    std::cout << message;
    getline(std::cin, input);
    //printf("%d", input.length()); //Check string length
    while(input.length() != 1){
        std::cout << "Invalid input, please enter a single character: ";
        getline(std::cin, input);
    }
}

bool switchAsk(){
    char input;
    bool returnFlag, errorFlag = true;

    while(errorFlag == true){
        std::cin >> input;
        switch(input){
        case 'Y':
        case 'y':
            errorFlag = false;
            returnFlag = true;
            break;
        case 'N':
        case 'n':
            errorFlag = false;
            returnFlag = false;
            break;
        default:
            std::cout << "Invalid input, try again: ";
            std::cin.clear();
            std::cin.ignore(999, '\n');
            errorFlag = true;
        }
    }
    std::cin.clear();
    std::cin.ignore(999, '\n');
    return returnFlag;
}

void cinCheckInt(int &input, const int &maxSize, const int &minSize, const std::string &message){
    std::cout << message;
    while(true){
        while(!(std::cin >> input)){
            std::cout << "Invalid input, please try again with a single number: ";
            std::cin.clear();
            std::cin.ignore(999, '\n');
        }
        //Checks if the value is correct
        if(!((input >= minSize)&&(input<=maxSize))){
            std::cout << "Please introduce a valid number: ";
        }
        else{
            break;
        }
    }
    std::cin.clear();
    std::cin.ignore(999, '\n');
}
