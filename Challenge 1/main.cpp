#include <iostream>
#include <random>
#include <chrono>
#include <thread>

#define MAX_ZOMBIE_HEALTH 100
#define MAX_SOLDIER_HEALTH 200

void cin(int &input); //Custom made function to prevent user from introducing negative values

int main(){
    //Declaration and Initialization of Zombie and Soldier Stats
    int nZombies = 0, nSoldiers = 0;
    int nZombieDeaths = 0, nSoldierDeaths = 0;
    int zombieAttack = 20, soldierAttack = 50;
    int zombieHealth = MAX_ZOMBIE_HEALTH, soldierHealth = MAX_SOLDIER_HEALTH;
    float zombieAccuracy = 0.35f, soldierAccuracy = 0.8f;

    //Random Value Generation
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count(); //Generate Seed from absolute time
    std::default_random_engine eng(seed); //Create random engine object
    std::uniform_real_distribution<float> realDist(0.0f, 1.0f); //Create uniform real distribution object

    //Start of the game. User is asked to define the number of soldiers and zombies
    std::cout<<"\t***Welcome to battle Simulator 4000!***\n\n"<<"Introduce the number of zombies: ";
    cin(nZombies);
    std::cout<<"Introduce the number of soldiers: ";
    cin(nSoldiers);
    std::cout<<"\n"<<"Number of Zombies: "<<nZombies<<std::endl<<"Number of Soldiers: "<<nSoldiers<<"\n\n";
    std::cout<<"\t___THE BATTLE WILL START SHORTLY___\n\n"<<"\t\t*Battle Noises*\n\n";

    std::this_thread::sleep_for (std::chrono::seconds(3)); //Wait 2 seconds to simulate "battle time"

    //Battle Simulation
    while((nZombies!=0)&&(nSoldiers!=0)){//While any team has remaining members, the battle will continue.

        if(realDist(eng)<=zombieAccuracy){//Checks if zombie hits successfully
            soldierHealth-=zombieAttack;
        }
        if(realDist(eng)<=soldierAccuracy){//Checks if soldier hits successfully
            zombieHealth-=soldierAttack;
        }
        if(zombieHealth<=0){//Checks if zombie has been killed
            nZombies--;
            nZombieDeaths++;
            zombieHealth = MAX_ZOMBIE_HEALTH;//Brings forward next zombie
        }
        if(soldierHealth<=0){//Checks if soldier has been killed
            nSoldiers--;
            nSoldierDeaths++;
            soldierHealth = MAX_SOLDIER_HEALTH;//Brings forward next soldier
        }

    }

    //Battle results
    std::cout<<"THE BATTLE IS OVER!\n\n";
    if(nZombies==0){
        std::cout<<"SOLDIERS WON!\n\n";
    }
    else std::cout<<"ZOMBIES WON!\n\n";
    std::cout<<"Number of Casualties:\n"<<"Zombies Killed: "<<nZombieDeaths<<std::endl<<"Soldiers Killed: "<<nSoldierDeaths<<std::endl;
    std::cout<<"\nNumber of Survivors:\n"<<"Remaining Zombies: "<<nZombies<<std::endl<<"Remaining Soldiers: "<<nSoldiers<<std::endl;

}

void cin(int &input){
    do{
        std::cin>>input;
        if(input<=0) std::cout<<"Please introduce a positive value.\n";

    }while(input<=0);
}

