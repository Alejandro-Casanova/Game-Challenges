#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "Player.h"
#include "Board.h"
#include "AI.h"

#define MAXBOARDSIZE 15
#define MINBOARDSIZE 3

const char AI_Mark = '$';
const std::string AI_Name = "AI Player";

Player setPlayer(int playerNumber); //Sets players 1 and 2 from user input
void cinCheckChar(std::string &input, const std::string &message);//Asks for a single character input
bool switchAsk();//Returns true if 'Y' is typed in and false if 'N' is typed in.
void cinCheckInt(int &input, const int &maxSize, const int &minSize, const std::string &message = "");

enum class GameModes {SINGLE_PLAYER, MULTI_PLAYER};

int main()
{
    int boardSize = 0;
    GameModes gameMode = GameModes::MULTI_PLAYER;//Sets multi_player by default
    std::vector<Player> player;//Player vector created
    std::cout << "Hello! Welcome to tic-tac-toe!\n";
    std::cout << "There are 2 Game Modes available:\n1) Single-Player: Play against the machine! (Board Size: 3x3) (Unbeatable, lol)\n";
    std::cout << "2) Multi-Player: Play with your friends! (Board size: up to 15x15) (Number of Players: 2-3)\n";

    //Set Game Mode
    std::cout << "\nDo you wish to play in Multi-Player Mode? (Y/N): ";
    if(switchAsk() == false){//Set game mode to Single-player if answer is negative (game is multi-player by default)
        gameMode = GameModes::SINGLE_PLAYER;
    }

    //Set Board
    if(gameMode == GameModes::SINGLE_PLAYER){
        boardSize = MINBOARDSIZE;
    }else{
        cinCheckInt(boardSize, MAXBOARDSIZE, MINBOARDSIZE, "Indicate desired board width (between 3 and 15): ");
    }
    Board::resizeBoard(boardSize);//Board set to size

    //Set Players
    if(gameMode == GameModes::SINGLE_PLAYER){//Set for Single-Player Mode
        std::cout << "Single-Player Mode Selected!\nDo you wish to move first? (Y/N): ";
        if(switchAsk() == true){
            player.push_back(setPlayer(0));
            player.push_back(Player(AI_Name, AI_Mark));
            AI::AIInit(player[0].getMark(), AI_Mark, MINBOARDSIZE);
        }else{
            //std::cout << std::endl;
            player.push_back(Player(AI_Name, AI_Mark));
            player.push_back(setPlayer(0));
            AI::AIInit(player[1].getMark(), AI_Mark, MINBOARDSIZE);
        }

    }else{//Set for multi-player mode
        player.push_back(setPlayer(1));
        player.push_back(setPlayer(2));
        std::cout << "\nDo you wish to add a third player? (Not recommended for boards <5x5) (Y/N): ";
        if(switchAsk() == true){//Set third player
                player.push_back(setPlayer(3));
        }
    }


    std::cout<<"\nThe Game Is Ready!\n";
    system("Pause");

    //Game Starts
    boardSize = Board::getSize();
    bool isDone = false;

    while(isDone == false){
        Board::printBoard();
        int turn = 0;
        for(int i = 0; i < boardSize*boardSize; i++){//The game keeps on until the board is full or any player wins
            if((gameMode == GameModes::SINGLE_PLAYER) && (player[turn].getName() == AI_Name)){
                AI::performMove(AI::getBestMove(AI_Mark, 0), AI_Mark);
                Board::printBoard();
                std::cout << AI_Name << " moved!\n";
            }else{
                std::cout<<player[turn].getName()<<"! It's your turn!\n";
                Board::askForMove(player[turn].getMark());
                Board::printBoard();
            }

            //Checks for win flag
            player[turn].setWinFlag(Board::checkVictory(player[turn].getMark()));
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

        //Game termination or restart
        std::cout << "\nDo you wish to play again? (Y/N): ";
        if(switchAsk() == true){
            Board::clearBoard();
        }else{
            isDone = true;
        }
    }
}

Player setPlayer(int playerNumber){
    std::string inputName, mark;
    if(playerNumber != 0){
        std::cout<<"\nPlayer "<<playerNumber<<", please enter your name: ";
    }else{
        std::cout << "Please enter your name: ";
    }
    getline(std::cin, inputName); //Get player name
    while(inputName.length() == 0){//Prevents name from being empty string
        std::cout << "Please introduce a valid name: ";
        getline(std::cin, inputName);
    }
    cinCheckChar(mark, "Now enter the symbol you want to play with: "); //Get single caracter
    Player player(inputName, mark.front());
    std::cout<<"Welcome "<<inputName<<"!\n";
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
        input = _getch();
        std::cout << input;

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
            std::cout << "\nInvalid input, try again: ";
            errorFlag = true;
        }
    }
    std::cout << std::endl;
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
