#pragma once

#include <string>

#include "Enemies.h";
#include "Characters.h"

void bigSlimeConstructor(std::string& name, int& health, std::string newName = "Big Slime");
void bigSlimeOnDeath(Character& player, Enemy& self);
void bigSlimeActionAI(Character& player, Enemy& self);