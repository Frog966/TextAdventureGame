#pragma once

#include "Slime.h";
#include "Characters.h";

enum class EnemyTypeList {
    Slime,
    Goblin
};

class Enemy {
private:
    EnemyTypeList enemyType;

    int health = 0;
    std::string name;
public:
    Enemy(EnemyTypeList et, std::string newName = ""); // Constructor

    // Getters
    int getHealth();
    std::string getName();
    EnemyTypeList getType();

    // Setters
    int increaseHealth(int amount);
    int decreaseHealth(int amount);

    // Enemy AI stuff
    void performOnDeath(Character& player);
    void performRandomAction(Character& player);
};