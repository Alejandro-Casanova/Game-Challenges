#include "enemy.h"

enemy::enemy(){

}

enemy::enemy(const std::string &name, const char &symbol, const int &rowVal, const int &colVal)
    : _name(name), _symbol(symbol), rowPosition(rowVal), colPosition(colVal){

    switch(symbol){
    case zombieChar:
        health = ZHEALTH;
        attackDamage = ZATTACK;
        attackPrecision = ZPRES;
        break;
    case skeletonChar:
        health = SHEALTH;
        attackDamage = SATTACK;
        attackPrecision = SPRES;
        break;
    default:
        assert(true == false);
        break;
    }
}

enemy::~enemy()
{

}

int enemy::attack(std::string &message){
    std::stringstream buffer;//Holds message
    if(getRandom() < attackPrecision){
        buffer << _name << " inflicted: " << attackDamage << " Damage Points.\n";
        message = buffer.str();
        return attackDamage;
    }else{
        buffer << _name << " missed!\n";
        message = buffer.str();
        return 0;
    }
}

void enemy::receiveDamage(const int &damageVal){
    health -= damageVal;
}

float enemy::getRandom() const{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count(); //Generate Seed from absolute time
    static std::default_random_engine eng(seed); //Create random engine object
    std::uniform_real_distribution<float> realDist(0.0f, 1.0f); //Create uniform real distribution object
    return realDist(eng);
}

int enemy::getRowPosition() const{
    return rowPosition;
}

int enemy::getColPosition() const{
    return colPosition;
}

int enemy::getHealth() const{
    return health;
}

std::string enemy::getName() const{
    return _name;
}

void enemy::setPosition(const int &rowVal, const int &colVal){
    rowPosition = rowVal;
    colPosition = colVal;
}

void enemy::setStats(const int &damage, const int &precision, const int &healthVal){
    attackDamage = damage;
    attackPrecision = precision;
    health = healthVal;
}
