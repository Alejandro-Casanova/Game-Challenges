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
#define ZXP 25

//Skeleton STATS
#define SATTACK 15
#define SPRES 0.5f
#define SHEALTH 100
#define SXP 25

//Dragon STATS
#define DATTACK 500
#define DPRES 0.6f
#define DHEALTH 600
#define DXP 500

class enemy
{
    public:
        static const char zombieChar = 'Z';
        static const char skeletonChar = 'S';
        static const char dragonChar = 'D';

        enemy();
        enemy(const std::string &name, const char &symbol, const int &rowVal, const int &colVal);
        virtual ~enemy();

        int attack(std::vector<std::string> &messageVector);//Returns damage points inflicted
        void receiveDamage(const int &damageVal); //Receives Damage


        int getRowPosition() const{return _rowPosition;}
        int getColPosition() const{return _colPosition;}
        int getHealth() const{return _health;}
        int getXp() const{return _xp;}
        std::string getName() const{return _name;}
        char getSymbol() const{return _symbol;}

    private:
        int _rowPosition, _colPosition;
        std::string _name;
        char _symbol;

        //Main stats
        int _attackDamage, _health, _xp;
        float _attackPrecision;

        float getRandom() const;//Returns random value between 0 and 1
        void setPosition(const int &rowVal, const int &colVal);
        void setStats(const int &damage, const int &precision, const int &healthVal);

        friend class map;
};

#endif // ENEMY_H
