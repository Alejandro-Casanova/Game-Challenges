#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class enemy
{
    public:
        enemy(std::string name, char symbol);
        virtual ~enemy();

        int getRowPosition() const;
        int getColPosition() const;

    private:
        int rowPosition, colPosition;
        std::string _name;
        char _symbol;

        void setPosition(const int &rowVal, const int &colVal);


        friend class map;
};

#endif // ENEMY_H
