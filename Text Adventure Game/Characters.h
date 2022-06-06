#pragma once

#include <vector>

// A string array containing all the player jobs
// Enums are difficult to iterate and too much trouble to turn into lists for the job listing part of the game
extern std::string jobList[1] = {
    "KNIGHT"
};

// A list of player actions that could last more than 1 turn
enum class PlayerBehaviourList {
    None,
    Guard,
};

class Character {
private:
    PlayerBehaviourList currPlayerBehaviour = PlayerBehaviourList::None;

    std::string job;
    std::string name;

    int health = 0;
    int attack = 0;
    float guardDmgMultiplier = 0;
public:
    Character(std::string playerClass); // Constructor

    // Getters
    std::string getJob();
    std::string getName();
    int getHealth();
    int getAttack();
    float getGuardDmgMultiplier();
    PlayerBehaviourList getCurrPlayerBehaviour();

    // Setters
    int increaseHealth(int amount);
    int decreaseHealth(int amount);
    void setCurrPlayerBehaviour(PlayerBehaviourList newBehaviour);
};