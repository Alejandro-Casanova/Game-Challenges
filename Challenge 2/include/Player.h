#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

class Player
{
    public:
       Player(std::string name, char mark);
       std::string getName() const;
       char getMark() const;
       bool getWinFlag() const;
       void setWinFlag(bool val);

    private:
        const std::string _name;
        const char _mark;
        bool winFlag = false;
};

#endif // PLAYER_H
