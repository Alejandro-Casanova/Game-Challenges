#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>
#include <sstream>
#include <random>
#include <chrono>
#include <cassert>

//ZOMBIE STATS
#define ZATTACK 10
#define ZPRES 0.4f
#define ZHEALTH 150

//Skeleton STATS
#define SATTACK 15
#define SPRES 0.5f
#define SHEALTH 100

class enemy
{
    public:
        static const char zombieChar = 'Z';
        static const char skeletonChar = 'S';

        enemy();
        enemy(const std::string &name, const char &symbol, const int &rowVal, const int &colVal);
        virtual ~enemy();

        int attack(std::string &message);//Returns damage points inflicted
        void receiveDamage(const int &damageVal); //Receives Damage


        int getRowPosition() const;
        int getColPosition() const;
        int getHealth() const;
        std::string getName() const;

    private:
        int rowPosition, colPosition;
        std::string _name;
        char _symbol;

        //Main stats
        int attackDamage, health;
        float attackPrecision;

        float getRandom() const;//Returns random value between 0 and 1
        void setPosition(const int &rowVal, const int &colVal);
        void setStats(const int &damage, const int &precision, const int &healthVal);

        friend class map;
};

#endif // ENEMY_H
