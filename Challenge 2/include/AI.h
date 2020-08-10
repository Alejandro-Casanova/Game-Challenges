#ifndef AI_H
#define AI_H

#include "Board.h"
#include <climits>

struct AIMove{
    AIMove(){};
    AIMove(const int &Score, const int &Depth) : score(Score), depth(Depth) {};

    int row;
    int col;
    int score;
    int depth;//Used to choose moves that lead to victory faster
};

class AI{
    public:
        static void AIInit(const char &playerChar, const char &aiChar, const char &boardSize); //AI must know the player's mark
        static AIMove getBestMove(const char &moveChar, const int &depth);//First call must be made with depth = 0
        static void performMove(const AIMove &move, const char &moveChar);

    private:
        static char playerMark;
        static char aiMark;
        static int boardSize;
};

#endif // AI_H
