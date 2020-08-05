#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <sstream>
#include <random>
#include <chrono>
#include <cmath>

//Player Default Stats
#define PHEALTH 200
#define PATTACK 50
#define PPRES 0.75f
#define LEVELUPXP 100 //XP required to level up
#define PDEFENCE 0

//Player Level Up Values
#define LHEALTH 20
#define LATTACK 5
#define LPRES 0.95 //Each time player levels up: presicion^LPRES (will be closer to 1 each time)
#define LDEF 2



class player
{
    public:
        player();

        int attack(std::string &message); //Returns attack damage inflicted
        void receiveDamage(const int &damageVal); //Receives Damage
        void gainXp(const int &xp, std::vector<std::string> &messageVector);

        int getRowPosition() const{return _rowPosition;}
        int getColPosition() const{return _colPosition;}
        int getAttack() const{return _attackDamage;}
        int getDefence() const{return _defence;}
        float getPrecision() const{return _attackPrecision;}
        int getHealth() const{return _health;}
        int getMaxHealth() const{return _maxHealth;}
        int getXp() const{return _xpCount;}
        int getMaxXp() const{return _maxXP;}
        int getLevel() const{return _levelCount;}

    private:
        int _rowPosition, _colPosition;

        //Main stats
        int _attackDamage, _defence, _health, _maxHealth;
        float _attackPrecision;
        int _xpCount, _maxXP, _levelCount;

        float getRandom() const;
        void setPosition(const int &rowVal, const int &colVal);
        void setStats(const int &damage, const int &precision, const int &healthVal);

        friend class map;

};

#endif // PLAYER_H
