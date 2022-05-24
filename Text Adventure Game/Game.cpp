#include <string>
#include <iostream>
#include <algorithm>    // std::copy_if, std::distance
#include <functional>

#include "Game.h"
#include "Enemies.h"
#include "Characters.h"

void clearCIn() {
	std::cin.clear();
	std::cin.ignore(256, '\n');
}

bool Game::isPlayerDead() {
	return currPlayer.getHealth() < 1;
}

void Game::SetIsFightingTrue() { isFighting = true; }
void Game::SetIsFightingFalse() { isFighting = false; }

// Populate encounter list here
// A randomizer can be considered here but requires design balancing
// Multiple enemies can be added but take care to not overdo it
void Game::SetUpEncounterList() {
	encounterList = {
		{
			EnemyTypeList::Slime
		},
		{
			EnemyTypeList::Slime
		},
	};
}

void Game::SetUpPlayer() {
	int selectedJob = NULL;
	int jobListSize = std::size(jobList);

	std::cout << "But before you go...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << std::endl;
	std::cout << "Do you remember your class?" << std::endl;

	auto ChooseYourJob = [&]() -> void {
		// Display all jobs
		for (int i = 0; i < jobListSize; ++i) {
			std::cout << (i + 1) << ". " << jobList[i] << std::endl;
		}

		std::cout << "Enter your choice: ";
		std::cin >> selectedJob;

		std::cout << std::endl;
	};

	ChooseYourJob();

	// Error handling for last cin (selecting your class)
	while (std::cin.fail() || selectedJob > jobListSize || selectedJob < 1) {
		if (std::cin.fail()) {
			std::cout << "Please enter a number.";
		}
		else if (selectedJob > jobListSize) {
			std::cout << "Your number has exceeeded the number of choices.";
		}
		else if (selectedJob < 1) {
			std::cout << "Your number is invalid";
		}

		std::cout << std::endl;

		clearCIn();

		ChooseYourJob();
	}

	std::string currJob = jobList[selectedJob - 1];

	// C++ does not allow strings in switch cases so we're using if/else
	// Please double check jobList definition in Characters.cpp
	if (std::find(std::begin(jobList), std::end(jobList), currJob) != std::end(jobList)) {
		currPlayer = Character(currJob); // Redefine currPlayer

		clearCIn();

		std::cout << "So you're a " << currPlayer.getJob() << " then...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else {
		std::cout << "Unknown job found: " << selectedJob - 1 << std::endl;
	}
}

// Sets up current encounter
void Game::SetUpCurrEncounter() {
	std::vector<EnemyTypeList>& currEnemyTypeList = encounterList[currEncounter]; // Just a temp declaration for the current enemy type list for easier reading

	enemyList.clear(); // Empty the enemy list first

	for (int i = 0; i < currEnemyTypeList.size(); ++i) {
		enemyList.push_back(Enemy(currEnemyTypeList[i])); // Push a newly created enemy into enemyList
	}
}

// Check if player has died or other things that happen to player at end of turn
void Game::CheckPlayerAfterTurn() {
	if (isPlayerDead()) {
		SetIsFightingFalse();
	}
	else {
		// Reset player behaviour if player isn't dead
		switch (currPlayer.getCurrPlayerBehaviour()) {
			case PlayerBehaviourList::Guard: { // Player stops guarding after enemies' turns
				currPlayer.setCurrPlayerBehaviour(PlayerBehaviourList::None);
				std::cout << std::endl << "You stop guarding." << std::endl;

				break;
			}
			default:
				break;
		}
	}
}

// Check if any enemy has died or other things that happen to enemies at end of turn
void Game::CheckEnemiesAfterTurn() {	 
	std::vector<Enemy> alive = {}; // To store all alive enemies to redefine enemyList later. Make sure to start as empty vector

	//std::cout << std::endl;

	for (int i = 0; i < enemyList.size(); ++i) {
		// If enemy is dead, add to dead vector. Else, add to alive vector
		if (enemyList[i].getHealth() <= 0) {
			enemyList[i].performOnDeath(currPlayer); // Perform this enemy's on-death action
		}
		else {
			alive.push_back(enemyList[i]);
		}
	}

	// Redefine enemyList to only alive enemies
	enemyList = alive;

	// All enemies are dead
	if (enemyList.size() <= 0) {
		SetIsFightingFalse();
		currEncounter++; // Progress currEncounter

		std::cout << std::endl << "It seems you've defeated all the enemies here." << std::endl;
		std::cout << "Moving on to the next area..." << std::endl;
	}
}

// Choose an enemy to attack here
void TargetEnemySelect(std::vector<Enemy>& enemyList, Character& currPlayer) {
	int selectedEnemy = 0;
	int enemyListSize = enemyList.size();

	// Enemy selection
	auto TargetEnemySelect = [&]() -> void {
		std::cout << "Select which enemy you want to attack:" << std::endl;

		// Choose which enemy to attack
		for (int i = 0; i <= enemyListSize; ++i) {
			std::cout << (i + 1) << ". ";

			if (i == enemyListSize) {
				std::cout << "Cancel";
			}
			else {
				Enemy currEnemy = enemyList[i];

				std::cout << currEnemy.getName() << " (HP: " << currEnemy.getHealth() << ")";
			}

			std::cout << std::endl;
		}

		std::cout << "Enter your choice: ";
		std::cin >> selectedEnemy;

		std::cout << std::endl;
	};

	TargetEnemySelect();

	// Error handling for last cin (selecting your target)
	// Adding 1 to enemyListSize because of back button
	// selectedEnemy cannot be less than 1
	while (std::cin.fail() || selectedEnemy > enemyListSize + 1 || selectedEnemy < 1) {
		if (std::cin.fail()) {
			std::cout << "Please enter a number.";
		}
		else if (selectedEnemy > enemyListSize + 1) {
			std::cout << "Your number has exceeeded the number of choices.";
		}
		else if (selectedEnemy < 1) {
			std::cout << "Your number is invalid";
		}

		std::cout << std::endl;

		clearCIn();

		TargetEnemySelect();
	}

	// Using if/else because switch case requires a const int and therefore won't accept enemyListSize
	// Attack target enemy from enemy list
	// Back button (selectedEnemy == enemyListSize + 1) will do nothing and CurrEncounterLoop() will restart the loop
	if (selectedEnemy != enemyListSize + 1) {
		Enemy& selectedEnemyObj = enemyList[selectedEnemy - 1];

		// Enemy will also lose health when decreaseHealth() is called
		int healthLoss = selectedEnemyObj.decreaseHealth(currPlayer.getAttack());

		std::cout << "You attacked " << selectedEnemyObj.getName() << " for " << healthLoss << " damage." << std::endl << std::endl;
	}
}

void Game::DoPlayerTurn() {
	int selectedAction = 0;

	// Player action selection section
	auto PlayerActionSelection = [&]() -> void {
		std::cout << currPlayer.getName() << " (HP: " << currPlayer.getHealth() << ")" << std::endl << std::endl;

		std::cout << "What would you do?" << std::endl;
		std::cout << "1. Attack" << std::endl;
		std::cout << "2. Guard" << std::endl;
		std::cout << "Enter your choice: ";
		std::cin >> selectedAction;

		std::cout << std::endl;
	};

	PlayerActionSelection();

	// Error handling for last cin (selecting your action)
	while (std::cin.fail() || selectedAction > 2 || selectedAction < 1) {
		if (std::cin.fail()) {
			std::cout << "Please enter a number.";
		}
		else if (selectedAction > 2) {
			std::cout << "Your number has exceeeded the number of choices.";
		}
		else if (selectedAction < 1) {
			std::cout << "Your number is invalid";
		}

		std::cout << std::endl;

		clearCIn();

		PlayerActionSelection();
	}

	switch (selectedAction) {
		case 1:
			TargetEnemySelect(enemyList, currPlayer);
			break;
		case 2:
			currPlayer.setCurrPlayerBehaviour(PlayerBehaviourList::Guard); // Set Player's action to guard
			std::cout << "You begin guarding..." << std::endl << std::endl;
			break;
	}

	CheckEnemiesAfterTurn();
}

// Make every enemy perform their action for their turn
void Game::DoEnemiesTurn() {
	for (int i = 0; i < enemyList.size(); ++i) {
		enemyList[i].performRandomAction(currPlayer);

		// If player is dead, break this loop
		if (isPlayerDead()) { break; }
	}

	CheckPlayerAfterTurn();
}

// Displays current encounter until player or all enemies die
void Game::CurrEncounterLoop() {
	while (isFighting) {
		std::cout << "====================================================" << std::endl;

		// Display all enemies and their HP
		for (int i = 0; i < enemyList.size(); ++i) {
			Enemy currEnemy = enemyList[i];

			std::cout << currEnemy.getName() << " (HP: " << currEnemy.getHealth() << ")" << std::endl;
		}

		std::cout << std::endl;

		DoPlayerTurn();
		DoEnemiesTurn();

		std::cout << "====================================================" << std::endl << std::endl;
	}
}

// Sets up the game
void Game::StartGame() {
	SetUpEncounterList();

	std::cout << "Hello there, player!";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "You're trapped inside a dungeon.";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "And your only way out is blocked by monsters...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	SetUpPlayer();

	std::cout << "I wish you good luck.";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << std::endl;

	// Player must fight through all encounters without dying to beat the game
	while (currEncounter < encounterList.size() && currPlayer.getHealth() > 0) {
		SetUpCurrEncounter(); // Instantiate the enemies first

		SetIsFightingTrue(); // Set encounter loop bool to true

		if (currEncounter == encounterList.size() - 1) {
			std::cout << "This seems to be the last room in the dungeon...";

			// Pause for so player would maybe pay attention
			clearCIn();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl;
		}

		std::cout << "You have encountered " << (encounterList[currEncounter].size() > 1 ? "a group of enemies" : "an enemy") << "!" << std::endl;

		CurrEncounterLoop(); // Begin displaying the encounter. Has its own while loop for combat
	}

	// Game Over Stuff
	if (currEncounter >= encounterList.size()) { // Player has beaten all encounters
		std::cout << "You did it! You've escaped the dungeon!" << std::endl;
	}
	else if (isPlayerDead()) {
		std::cout << "Oh no... You've been defeated. Better luck next time!" << std::endl;
	}

	std::cout << std::endl << "GAME OVER" << std::endl;
}

// Constructor
Game::Game() {
	StartGame();
}