#include "player.h"

player::player() : _rowPosition(0), _colPosition(0), _health(PHEALTH),_maxHealth(PHEALTH), _attackDamage(PATTACK), _attackPrecision(PPRES), _xpCount(0), _maxXP(LEVELUPXP), _levelCount(1), _defence(PDEFENCE){
}

int player::attack(std::string &message){
    std::stringstream buffer;//Holds message

    if(getRandom() < _attackPrecision){
        buffer << "You inflicted: " << _attackDamage << " Damage Points.\n";
        message = buffer.str();
        return _attackDamage;
    }else{
        buffer << "You missed!\n";
        message = buffer.str();
        return 0;
    }
}

void player::receiveDamage(const int &damageVal){
    if(damageVal > _defence){//Damage is only received if its value is higher than the defence value
        _health -= (damageVal - _defence);
    }
    if(_health < 0){
        _health = 0;
    }
}

void player::gainXp(const int &xp, std::vector<std::string> &messageVector){
    std::stringstream message;

    _xpCount += xp;

    //Level UP
    while(_xpCount >= LEVELUPXP){
        _xpCount -= LEVELUPXP;
        _levelCount++;

        //Stats improve
        _maxHealth += LHEALTH;
        _health = _maxHealth; //Health restarts
        _attackDamage += LATTACK;
        _attackPrecision = std::pow(_attackPrecision, LPRES); //Each time will be closer to 1
        _defence += LDEF;

        //Get message
        message << "Congratulations! You reached Level " << _levelCount << "!" << std::endl;
    }
    messageVector.push_back(message.str());
}

float player::getRandom() const{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count(); //Generate Seed from absolute time
    static std::default_random_engine eng(seed); //Create random engine object
    std::uniform_real_distribution<float> realDist(0.0f, 1.0f); //Create uniform real distribution object
    return realDist(eng);
}

void player::setPosition(const int &rowVal, const int &colVal){
    _rowPosition = rowVal;
    _colPosition = colVal;
}

void player::setStats(const int &damage, const int &precision, const int &healthVal){
    _attackDamage = damage;
    _attackPrecision = precision;
    _health = healthVal;
}
