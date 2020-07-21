#include <iostream>
#include <string>

#include "Player.h"
#include "Board.h"

Player setPlayer(int playerNumber); //Sets players 1 and 2 from user input

int main()
{
    Board board;//Board object created
    std::cout << "Hello! Welcome to tic-tac-toe!\n";

    //Set Players
    Player player1 = setPlayer(1);
    Player player2 = setPlayer(2);
    std::cout<<"\nThe Game Is Ready!\n";
    system("Pause");

    //Game Starts
    board.printBoard();
    for(int i = 0; i < SIZEX*SIZEY; i++){//The game keeps on until the board is full or any player wins
        static bool turn=false;
        if(turn==false){//First player's turn
            std::cout<<player1.getName()<<"! It's your turn!\n";
            board.setTile(player1.getMark());
            board.printBoard();
            turn=true;
            player1.setWinFlag(board.checkVictory(player1.getMark()));//Checks if player 1 has won
        }else{//Second player's turn
            std::cout<<player2.getName()<<"! It's your turn!\n";
            board.setTile(player2.getMark());
            board.printBoard();
            turn=false;
            player2.setWinFlag(board.checkVictory(player2.getMark()));//Checks if player 2 has won

        }
        if((player1.getWinFlag() == true) || (player2.getWinFlag() == true)){//If any player wins before the board is full, the loop is interrupted
            break;
        }
    }

    //Results are printed
    std::cout<<"The Game is Over! Result: ";
    if(player1.getWinFlag() == true){
        std::cout<<player1.getName()<<" wins!";
    }
    else if(player2.getWinFlag() == true){
        std::cout<<player2.getName()<<" wins!";
    }
    else{
        std::cout<<"Ties!";
    }


}

Player setPlayer(int playerNumber){
    std::string inputName;
    char mark;
    std::cout<<"\nPlayer "<<playerNumber<<", please enter your name: ";
    std::cin >> inputName;
    std::cout<<"Now enter the symbol you want to play with: ";
    std::cin>>mark;
    Player player(inputName, mark);
    return player;
}
