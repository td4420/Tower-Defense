#pragma once
#include "Tower.h"
class Player
{
	int lives = 20;
	int money = 200;

	std::vector <Tower*> towerList;

	void BuildTower(float x, float y, int towerType);
	Player();
};

