#pragma once

#include "Characters.h";

enum class EnemyTypeList {
    Slime,
    BigSlime
};

enum class EnemyBehaviourList {
    None,
    Guard,
    Charge,
};

class Enemy {
private:
    EnemyTypeList enemyType;

    int health = 0;
    std::string name;
    float guardDmgMultiplier = 0.5;
public:
    EnemyBehaviourList currEnemyBehaviour = EnemyBehaviourList::None;

    Enemy(EnemyTypeList et, std::string newName = ""); // Constructor

    // Getters
    int getHealth();
    std::string getName();
    EnemyTypeList getType();
    float getGuardDmgMultiplier();
    EnemyBehaviourList getCurrEnemyBehaviour();

    // Setters
    int increaseHealth(int amount);
    int decreaseHealth(int amount);
    void setCurrEnemyBehaviour(EnemyBehaviourList newBehaviour);

    // Enemy AI stuff
    void performOnDeath(Character& player);
    void performRandomAction(Character& player);
};