#include <string>
#include <iostream>

#include "Enemies.h"
#include "Characters.h"
#include "Randomizers.h";

void slimeConstructor(std::string& name, int& health, std::string newName) {
	name = newName == "" ? "Slime" : newName;
	health = 100;
}

void slimeActionAI(Character& player, Enemy& self) {
	// Randomizer max must be number of cases in the switch case
	switch (intRand(2)) {
		case 0:
			std::cout << self.getName() << " seems nonchalant..." << std::endl;
			break;
		case 1: {
			// Player will also lose health when decreaseHealth() is called
			int healthLoss = player.decreaseHealth(10);

			std::cout << self.getName() << " tackles you! It deals " << healthLoss << " damage." << std::endl;
			break;
		}
		default:
			break;
	}
}

void slimeOnDeath(Character& player, Enemy& self) {
	// Randomizer max must be number of cases in the switch case
	switch (intRand(2)) {
	case 0:
		std::cout << self.getName() << " dies..." << std::endl;
		break;
	case 1:
		std::cout << self.getName() << " lets out a piercing death cry, which in human terms means 'jiggle violently then deflate'." << std::endl;
		break;
	default:
		break;
	}
}