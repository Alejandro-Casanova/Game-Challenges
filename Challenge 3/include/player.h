#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <sstream>
#include <random>
#include <chrono>

//Player Default Stats
#define PHEALTH 200
#define PATTACK 50
#define PPRES 0.75f

class player
{
    public:
        player();
        player(const int &rowVal, const int &colVal);

        int attack(std::string &message); //Returns attack damage inflicted
        void receiveDamage(const int &damageVal); //Receives Damage

        int getRowPosition() const;
        int getColPosition() const;
        int getHealth() const;

    private:
        int rowPosition, colPosition;

        //Main stats
        int attackDamage, health;
        float attackPrecision;

        float getRandom() const;
        void setPosition(const int &rowVal, const int &colVal);
        void setStats(const int &damage, const int &precision, const int &healthVal);

        friend class map;

};

#endif // PLAYER_H
