#include <string>
#include <iostream>

#include "Enemies.h";
#include "Characters.h"
#include "Randomizers.h";

void bigSlimeConstructor(std::string& name, int& health, std::string newName) {
	name = newName == "" ? "Big Slime" : newName;
	health = 500;
}

void bigSlimeActionAI(Character& player, Enemy& self) {
	switch (self.getCurrEnemyBehaviour()) {
		case EnemyBehaviourList::Charge: { // Do charge attack
			// Player will also lose health when decreaseHealth() is called
			int healthLoss = player.decreaseHealth(20);
			std::cout << self.getName() << " strikes you with all its weight! It deals " << healthLoss << " damage." << std::endl;

			self.setCurrEnemyBehaviour(EnemyBehaviourList::None); // Reset Big Slime's behaviour after charge attack

			break;
		}
		case EnemyBehaviourList::None: {
			// Randomizer max must be number of cases in the switch case
			switch (intRand(4)) {
			//switch (3) { // Testing only
				case 0: {
					std::cout << self.getName() << " jiggles menacingly..." << std::endl;
					break;
				}
				case 1: {
					// Player will also lose health when decreaseHealth() is called
					int healthLoss = player.decreaseHealth(10);

					std::cout << self.getName() << " tackles you! It deals " << healthLoss << " damage." << std::endl;
					break;
				}
				case 2: { // Big Slime is readying a strong attack
					self.setCurrEnemyBehaviour(EnemyBehaviourList::Charge);
					std::cout << self.getName() << " seems to be winding up its entire body for an attack!" << std::endl;
					break;
				}
				case 3: { // Big Slime is guarding. Resets on Game::CheckEnemiesAfterTurn()
					self.setCurrEnemyBehaviour(EnemyBehaviourList::Guard);
					std::cout << self.getName() << " seems to be stiffening itself." << std::endl;
					break;
				}
				default:
					break;
			}

			break;
		}
	}
}

void bigSlimeOnDeath(Character& player, Enemy& self) {
	// Randomizer max must be number of cases in the switch case
	switch (intRand(1)) {
		case 0:
			std::cout << self.getName() << " lets out a piercing death cry, which in human terms means 'jiggle violently then deflate'." << std::endl;
			break;
		default:
			break;
	}
}