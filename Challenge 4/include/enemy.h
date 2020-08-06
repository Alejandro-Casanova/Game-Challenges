#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>
#include <sstream>
#include <random>
#include <chrono>
#include <cassert>

//Army A STATS
#define AATTACK 20
#define APRES 0.7f
#define AHEALTH 100

//Army B STATS
#define BATTACK 20
#define BPRES 0.7f
#define BHEALTH 100

class enemy
{
    public:
        static const char AChar = 'A';
        static const char BChar = 'B';

        enemy();
        enemy(const std::string &name, const char &symbol, const int &rowVal, const int &colVal);
        virtual ~enemy();

        int attack() const;
        void receiveDamage(const int &damageVal); //Receives Damage
        enemy* findEnemy(const std::vector <enemy*> &enemyVector) const; //Returns pointer to closest enemy
        char getMove(enemy* enemyPtr) const; //Returns move char (w, a, s, d) that leads to closest enemy

        int getRowPosition() const{return _rowPosition;}
        int getColPosition() const{return _colPosition;}
        int getHealth() const{return _health;}
        std::string getName() const{return _name;}
        char getSymbol() const{return _symbol;}

    private:
        int _rowPosition, _colPosition;
        std::string _name;
        char _symbol;

        //Main stats
        int _attackDamage, _health;
        float _attackPrecision;

        float getRandom() const;//Returns random value between 0 and 1
        void setPosition(const int &rowVal, const int &colVal);
        void setStats(const int &damage, const int &precision, const int &healthVal);

        friend class map;
};

#endif // ENEMY_H
