#include <iostream>
#include <string>
#include <vector>

#include "Player.h"
#include "Board.h"

Player setPlayer(int playerNumber); //Sets players 1 and 2 from user input
void cinCheckChar(std::string &input, const std::string &message);//Asks for a single character input
bool switchAsk();//Returns true if 'Y' is typed in and false if 'N' is typed in.

int main()
{
    Board board;//Board object created
    std::vector<Player> player;//Player vector created
    std::cout << "Hello! Welcome to tic-tac-toe!\n";

    //Set Players
    player.push_back(setPlayer(1));
    player.push_back(setPlayer(2));
    std::cout << "\nDo you wish to add a third player? (Recommended for boards >5x5) (Y/N): ";
    if(switchAsk() == true){
            player.push_back(setPlayer(3));
    }
    std::cout<<"\nThe Game Is Ready!\n";
    system("Pause");

    //Game Starts
    board.printBoard();
    for(int i = 0; i < SIZEX*SIZEY; i++){//The game keeps on until the board is full or any player wins
        static bool turn=false;
        if(turn==false){//First player's turn
            std::cout<<player[0].getName()<<"! It's your turn!\n";
            board.setTile(player[0].getMark());
            board.printBoard();
            turn=true;
            player[0].setWinFlag(board.checkVictory(player[0].getMark()));//Checks if player 1 has won
        }else{//Second player's turn
            std::cout<<player[1].getName()<<"! It's your turn!\n";
            board.setTile(player[1].getMark());
            board.printBoard();
            turn=false;
            player[1].setWinFlag(board.checkVictory(player[1].getMark()));//Checks if player 2 has won

        }
        if((player[0].getWinFlag() == true) || (player[1].getWinFlag() == true)){//If any player wins before the board is full, the loop is interrupted
            break;
        }
    }

    //Results are printed
    std::cout<<"The Game is Over! Result: ";
    if(player[0].getWinFlag() == true){
        std::cout<<player[0].getName()<<" wins!";
    }
    else if(player[1].getWinFlag() == true){
        std::cout<<player[1].getName()<<" wins!";
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
