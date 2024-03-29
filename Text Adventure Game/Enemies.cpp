#include <string>
#include <iostream>

#include "Slime.h"
#include "Enemies.h"
#include "BigSlime.h"

// Just to handle any unknown enum class values
// Copied from https://stackoverflow.com/questions/11421432/how-can-i-output-the-value-of-an-enum-class-in-c11
template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e) {
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

// Constructor
Enemy::Enemy(EnemyTypeList et, std::string newName) {
    enemyType = et; // Set this new enemy's type
    
    switch (enemyType) {
        case EnemyTypeList::Slime:
            slimeConstructor(name, health, newName);
            break;
        case EnemyTypeList::BigSlime:
            bigSlimeConstructor(name, health, newName);
            break;
        default:
            std::cout << "Unknown enemy type found!: " << enemyType << std::endl;
            break;
    }
}

// Getters
int Enemy::getHealth() { return health; }
std::string Enemy::getName() { return name; }
EnemyTypeList Enemy::getType() { return enemyType; }
float Enemy::getGuardDmgMultiplier() { return guardDmgMultiplier; }
EnemyBehaviourList Enemy::getCurrEnemyBehaviour() { return currEnemyBehaviour; }

// Returns calculated health gain
int Enemy::increaseHealth(int amount) {
    int healthGain = amount;

    health += healthGain;

    return healthGain;
}

// Returns calculated health loss
int Enemy::decreaseHealth(int amount) {
    // Healthloss is affected by:
    // Whether player is guarding
    int healthLoss = amount * (getCurrEnemyBehaviour() == EnemyBehaviourList::Guard ? guardDmgMultiplier : 1);

    health -= healthLoss;

    return healthLoss;
}

void Enemy::performRandomAction(Character& player) {
    switch (enemyType) {
        case EnemyTypeList::Slime: 
            slimeActionAI(player, *this);
            break;
        case EnemyTypeList::BigSlime:
            bigSlimeActionAI(player, *this);
            break;
        default:
            std::cout << "Unknown enemy type trying to perform an action!: " << enemyType << std::endl;
            break;
    }
}

void Enemy::performOnDeath(Character& player) {
    switch (enemyType) {
        case EnemyTypeList::Slime:
            slimeOnDeath(player, *this);
            break;
        case EnemyTypeList::BigSlime:
            bigSlimeOnDeath(player, *this);
            break;
        default:
            std::cout << "Unknown enemy type trying to perform an on-death action!: " << enemyType << std::endl;
            break;
    }
}

void Enemy::setCurrEnemyBehaviour(EnemyBehaviourList newBehaviour) {
    currEnemyBehaviour = newBehaviour;
}