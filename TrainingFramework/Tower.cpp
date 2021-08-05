#include "stdafx.h"
#include "Tower.h"
#include <cmath>

Tower::Tower()
{
	o_Model = Model("../Resources/model.nfg");
	o_Texture.push_back(Texture("../ResourcesPacket/Textures/machineGunTower.tga"));
	range = 0.3f;
}

Tower::Tower(int type)
{
	towerType = type;
	if (towerType == 0)
	{
		o_Model = Model("../Resources/model.nfg");
		o_Texture.push_back(Texture("../ResourcesPacket/nen.tga"));
		damage = 10;
		range = 0.1f;
	}

	if (towerType == 1)
	{
		o_Model = Model("../Resources/model.nfg");
		o_Texture.push_back(Texture("../ResourcesPacket/nen.tga"));
		damage = 20;
		range = 0.3f;
	}
}

float Tower::CaculateDistanceToEnemies(Enemies *e)//must Enemies* or White Screen
{
	towerPos.x = 0.075f;// test only
	towerPos.y = -0.1f;// test only
	float deltaX = towerPos.x - (e->o_position.x + 0.075f);
	float deltaY = towerPos.y - (e->o_position.y - 0.1f);

	float distance = sqrtf(powf(deltaX, 2.0f) + powf(deltaY, 2.0f));

	return distance;

	//return 0;
}

void Tower::AddEnemiesInRange(vector <Enemies*> enemyWave)
{
	for (int i = 0; i < enemyWave.size(); i++)
	{
		float distance = CaculateDistanceToEnemies(enemyWave.at(i));

		if (distance <= range) {
			enemiesInRange.push_back(enemyWave.at(i));
			cout << "In!" << endl;
		}
	}
}

void Tower::RemoveEnemiesOutOfRange()
{
	if (enemiesInRange.size()!=0)
	{
		for (int i = 0; i < enemiesInRange.size(); i++)
		{
			float distance = CaculateDistanceToEnemies(enemiesInRange.at(i));

			if (distance > range) {
				enemiesInRange.erase(enemiesInRange.begin() + i);
				cout << "Out!" << endl;
			}
		}
	}
}

void Tower::Build(int x, int y)
{

}

void Tower::Shoot()
{

}

void Tower::SetTarget()
{
	if (!enemiesInRange.empty()) currentTarget = *enemiesInRange.front();
}