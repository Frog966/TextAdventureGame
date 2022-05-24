#include <string>
#include <iostream>

//#include "Enemies.h"
#include "Characters.h"
#include "Randomizers.h";

void slimeConstructor(std::string& name, int& health, std::string newName) {
	name = newName == "" ? "Slime" : newName;
	health = 100;
}

void slimeActionAI(Character& player, std::string slimeName) {
	// Randomizer max must be number of cases in the switch case
	switch (intRand(2)) {
		case 0:
			std::cout << slimeName << " seems nonchalant..." << std::endl;
			break;
		case 1: {
			// Player will also lose health when decreaseHealth() is called
			int healthLoss = player.decreaseHealth(10);

			std::cout << slimeName << " tackles you! It deals " << healthLoss << " damage." << std::endl;
			break;
		}
		default:
			break;
	}
}

void slimeOnDeath(Character& player, std::string slimeName) {
	// Randomizer max must be number of cases in the switch case
	switch (intRand(2)) {
	case 0:
		std::cout << slimeName << " dies..." << std::endl;
		break;
	case 1:
		std::cout << slimeName << " lets out a piercing death cry, which in human terms means 'jiggle violently then deflate'." << std::endl;
		break;
	default:
		break;
	}
}