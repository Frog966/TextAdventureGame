#pragma once

#include <string>
#include <vector>

#include "Enemies.h"

// Hold data of each enemy in an encounter
struct EnemyInfo {
    std::string name;
    EnemyTypeList type;
};

class Game {
private:
    int currEncounter = 0; // Keeps track of current encounter. Init as 0 immediately for convenience
    bool isFighting = false; // A bool to keep each encounter loop running

    // A list of encounters
    // Each encounter is a list of enemies defined by their enemy type including bosses
    // Will be populated in SetUpEncounterList()
    std::vector<std::vector<EnemyInfo>> encounterList;

    // A list of enemies
    // Will be populated in SetUpCurrEncounter();
    // Only contains the enemies of 1 encounter to reduce load
    std::vector<Enemy> enemyList;

    // C++ requires this to be defined immediately or in the constructor's initializer list
    // Do an immediate definition as the default first. Will be redefined later in SetUpPlayer()
    Character currPlayer = Character("KNIGHT");

    // Setters
    void SetIsFightingTrue();
    void SetIsFightingFalse();

    bool isPlayerDead();

    void SetUpPlayer();
    void SetUpEncounterList();
    void SetUpCurrEncounter();
    void TargetEnemySelect();
    void DoPlayerTurn();
    void DoEnemiesTurn();
    void CurrEncounterLoop();
    void CheckPlayerAfterTurn();
    void CheckEnemiesAfterTurn();
    void StartGame();

    //void BeginEncounter();
    //void EndEncounter();
public:
    // Constructor
    Game();
};