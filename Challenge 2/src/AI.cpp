#include "AI.h"

char AI::playerMark = '0';
char AI::aiMark = '0';
int AI::boardSize = 0;

void AI::AIInit(const char &playerChar, const char &aiChar, const char &boardSize){
    playerMark = playerChar;
    aiMark = aiChar;
    AI::boardSize = boardSize;
}

AIMove AI::getBestMove(const char &moveChar, const int &depth){
    int depthCounter = depth;
    depthCounter++;

    if(Board::checkVictory(playerMark) == true){
        return AIMove(-10, depthCounter);
    }else if(Board::checkVictory(aiMark) == true){
        return AIMove(10, depthCounter);
    }
    std::vector<AIMove> moveVector;

    for(int i = 1; i <= boardSize; i++){
        for(int j = 1; j <= boardSize; j++){
            if(Board::getTile(i, j) == emptyTile){
                AIMove move, auxMove;
                move.row = i;
                move.col = j;
                Board::setTile(i - 1, j - 1, moveChar); //"setTile()" is indexed at 0!
                if(moveChar == aiMark){
                    //move.score = getBestMove(playerMark).score;
                    auxMove = getBestMove(playerMark, depthCounter);
                    move.score = auxMove.score;
                    move.depth = auxMove.depth;
                }else{
                    //move.score = getBestMove(aiMark).score;
                    auxMove = getBestMove(aiMark, depthCounter);
                    move.score = auxMove.score;
                    move.depth = auxMove.depth;
                }

                moveVector.push_back(move);

                Board::setTile(i - 1, j - 1, emptyTile);

            }
        }
    }
    AIMove moveMem;
    if(moveChar == playerMark){
        //moveMem.score = INT_MAX;
        for(int i = 0; i < moveVector.size(); i++){
            if((moveVector[i].score < moveMem.score) || (i == 0)){
                moveMem = moveVector[i];
            }else if((moveVector[i].score == moveMem.score) && (moveVector[i].depth < moveMem.depth)){
                moveMem = moveVector[i];
            }
        }
    }
    if(moveChar == aiMark){
        //moveMem.score = INT_MIN;
        for(int i = 0; i < moveVector.size(); i++){
            if((moveVector[i].score > moveMem.score) || (i == 0)){
                moveMem = moveVector[i];
            }else if((moveVector[i].score == moveMem.score) && (moveVector[i].depth < moveMem.depth)){
                moveMem = moveVector[i];
            }
        }
    }

    return moveMem;

}

void AI::performMove(const AIMove &move, const char &moveChar){
    Board::setTile(move.row - 1, move.col - 1, moveChar);
}
