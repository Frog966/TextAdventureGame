#include <string>
#include <iostream>
#include <algorithm> // For the std::transform()

#include "Characters.h"

std::string jobList[1] = {
    "KNIGHT"
};

// Constructor
Character::Character(std::string _job) {
    // Uppercasing "_job" to avoid errors
    std::transform(_job.begin(), _job.end(), _job.begin(), ::toupper);

    // C++ switch cases don't accept strings as cases so we're using if/else
    if (_job == "KNIGHT") {
        name = job = "Knight";

        health = 100;
        attack = 50;
        guardDmgMultiplier = 0.5;
    }
    else {
        std::cout << "Unknown player class found!: " << _job << std::endl;
    }
}

// Getters
std::string Character::getJob() { return job; }
std::string Character::getName() { return name; }
int Character::getHealth() { return health; }
int Character::getAttack() { return attack; }
float Character::getGuardDmgMultiplier() { return guardDmgMultiplier; }
PlayerBehaviourList Character::getCurrPlayerBehaviour() { return currPlayerBehaviour; }

// Returns calculated health gain
int Character::increaseHealth(int amount) {
    int healthGain = amount;

    health += healthGain;

    return healthGain;
}

// Returns calculated health loss
int Character::decreaseHealth(int amount) {
    // Healthloss is affected by:
    // Whether player is guarding
    int healthLoss = amount * (currPlayerBehaviour == PlayerBehaviourList::Guard ? guardDmgMultiplier : 1);

    health -= healthLoss;

    return healthLoss;
}

void Character::setCurrPlayerBehaviour(PlayerBehaviourList newBehaviour) {
    currPlayerBehaviour = newBehaviour;
}
