#include "enemy.h"

enemy::enemy(){

}

enemy::enemy(const std::string &name, const char &symbol, const int &rowVal, const int &colVal)
    : _name(name), _symbol(symbol), _rowPosition(rowVal), _colPosition(colVal){

    switch(symbol){
    case zombieChar:
        _health = ZHEALTH;
        _attackDamage = ZATTACK;
        _attackPrecision = ZPRES;
        _xp = ZXP;
        break;
    case skeletonChar:
        _health = SHEALTH;
        _attackDamage = SATTACK;
        _attackPrecision = SPRES;
        _xp = SXP;
        break;
    case dragonChar:
        _health = DHEALTH;
        _attackDamage = DATTACK;
        _attackPrecision = DPRES;
        _xp = DXP;
        break;
    default:
        assert(true == false);
        break;
    }
}

enemy::~enemy()
{

}

int enemy::attack(std::vector<std::string> &messageVector){
    std::stringstream buffer;//Holds message
    if(getRandom() < _attackPrecision){
        buffer << _name << " inflicted: " << _attackDamage << " Damage Points.\n";
        messageVector.push_back(buffer.str());
        return _attackDamage;
    }else{
        buffer << _name << " missed!\n";
        messageVector.push_back(buffer.str());
        return 0;
    }
}

void enemy::receiveDamage(const int &damageVal){
    _health -= damageVal;
}

float enemy::getRandom() const{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count(); //Generate Seed from absolute time
    static std::default_random_engine eng(seed); //Create random engine object
    std::uniform_real_distribution<float> realDist(0.0f, 1.0f); //Create uniform real distribution object
    return realDist(eng);
}

void enemy::setPosition(const int &rowVal, const int &colVal){
    _rowPosition = rowVal;
    _colPosition = colVal;
}

void enemy::setStats(const int &damage, const int &precision, const int &healthVal){
    _attackDamage = damage;
    _attackPrecision = precision;
    _health = healthVal;
}
