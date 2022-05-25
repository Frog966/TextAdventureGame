#pragma once

#include <string>

#include "Enemies.h"
#include "Characters.h"

void slimeConstructor(std::string& name, int& health, std::string newName = "Slime");
void slimeOnDeath(Character& player, Enemy& self);
void slimeActionAI(Character& player, Enemy& self);