#include "enemy.h"

enemy::enemy(){
}

enemy::enemy(const std::string &name, const char &symbol, const int &rowVal, const int &colVal)
    : _name(name), _symbol(symbol), _rowPosition(rowVal), _colPosition(colVal){

    switch(symbol){
    case AChar:
        _health = AHEALTH;
        _attackDamage = AATTACK;
        _attackPrecision = APRES;
        //_xp = ZXP;
        break;
    case BChar:
        _health = BHEALTH;
        _attackDamage = BATTACK;
        _attackPrecision = BPRES;
        //_xp = SXP;
        break;
    default:
        assert(true == false);
        break;
    }
}

enemy::~enemy(){
}

int enemy::attack() const{
    if(getRandom() < _attackPrecision){
        return _attackDamage;
    }else{
        return 0;
    }
}

void enemy::receiveDamage(const int &damageVal){
    _health -= damageVal;
}

enemy* enemy::findEnemy(const std::vector <enemy*> &enemyVector) const{
    int myRow = getRowPosition();
    int myCol = getColPosition();
    int distMem = 0;
    enemy* auxEnemyPtr = nullptr;

    for(int i = 0; i < enemyVector.size(); i++){
        int row = enemyVector[i]->getRowPosition();
        int col = enemyVector[i]->getColPosition();
        int dist = abs(row - myRow) + abs(col - myCol);

        if((dist < distMem) || (distMem == 0)){
            distMem = dist;
            auxEnemyPtr = enemyVector[i];
        }
    }
    assert(auxEnemyPtr != nullptr);
    return auxEnemyPtr;
}

char enemy::getMove(enemy* enemyPtr) const{
    int myRow = getRowPosition();
    int myCol = getColPosition();
    int row = enemyPtr->getRowPosition();
    int col = enemyPtr->getColPosition();
    int dy = myRow - row;
    int dx = myCol - col;

    if((abs(dx) > abs(dy)) || ((abs(dx) == abs(dy)) && ((abs(dx)%2)!=0))){
        if(dx < 0){
            return 'd';
        }else{
            return 'a';
        }
    }else{
        if(dy < 0){
            return 's';
        }else{
            return 'w';
        }
    }
    assert(false);
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
