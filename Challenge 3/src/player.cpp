#include "player.h"

player::player() : rowPosition(0), colPosition(0), health(PHEALTH), attackDamage(PATTACK), attackPrecision(PPRES){
}

player::player(const int &rowVal, const int &colVal) : rowPosition(rowVal), colPosition(colVal){
}

int player::attack(std::string &message){
    std::stringstream buffer;//Holds message{
    if(getRandom() < attackPrecision){
        buffer << "You inflicted: " << attackDamage << " Damage Points.\n";
        message = buffer.str();
        return attackDamage;
    }else{
        buffer << "You missed!\n";
        message = buffer.str();
        return 0;
    }
}

void player::receiveDamage(const int &damageVal){
    health -= damageVal;
}

int player::getRowPosition() const{
    return rowPosition;
}

int player::getColPosition() const{
    return colPosition;
}

int player::getHealth() const{
    return health;
}

float player::getRandom() const{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count(); //Generate Seed from absolute time
    static std::default_random_engine eng(seed); //Create random engine object
    std::uniform_real_distribution<float> realDist(0.0f, 1.0f); //Create uniform real distribution object
    return realDist(eng);
}

void player::setPosition(const int &rowVal, const int &colVal){
    rowPosition = rowVal;
    colPosition = colVal;
}

void player::setStats(const int &damage, const int &precision, const int &healthVal){
    attackDamage = damage;
    attackPrecision = precision;
    health = healthVal;
}
