#pragma once

#include <string>

//#include "Enemies.h"
#include "Characters.h"

void slimeConstructor(std::string& name, int& health, std::string newName = "Slime");
void slimeOnDeath(Character& player, std::string slimeName);
void slimeActionAI(Character& player, std::string slimeName);