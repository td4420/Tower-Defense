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
	o_Model = Model("../Resources/model.nfg");
	reloadSpeed = 0.1f;
	upgrade = 0;

	if (towerType == 0)//archer tower: small damage, medium range, fast reload
	{
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/archerTower.tga"));
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/archerTower2.tga"));
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/archerTower3.tga"));
		damage = 0;
		range = 1.0f;
		reloadTime = 5.0f;
		timeSinceLastShot = reloadTime;
		cost = 100;
	}

	if (towerType == 1)//mortar tower: huge damage, long range, very slow reload
	{
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/mortarTower.tga"));
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/mortarTower2temp.tga"));
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/mortarTower3temp.tga"));
		damage = 70;
		range = 0.5f;
		reloadTime = 20.0f;
		timeSinceLastShot = reloadTime;
		cost = 500;
	}

	if (towerType == 2)//slow tower
	{
		o_Texture.push_back("../ResourcesPacket/Textures/slowTower.tga");
		o_Texture.push_back("../ResourcesPacket/Textures/slowTower2.tga");
		o_Texture.push_back("../ResourcesPacket/Textures/slowTower3.tga");
		damage = 10;
		range = 0.3f;
		reloadTime = 10.0f;
		timeSinceLastShot = reloadTime;
		cost = 250;
	}

	if (towerType == 3)//chance tower: 3%-5% chance for huge damage, 10-20% chance for slow
	{
		o_Texture.push_back("../ResourcesPacket/Textures/witchTower.tga");
		o_Texture.push_back("../ResourcesPacket/Textures/witchTower2.tga");
		o_Texture.push_back("../ResourcesPacket/Textures/witchTower3.tga");
		damage = 0;
		range = 0.7f;
		reloadTime = 6.0f;
		timeSinceLastShot = reloadTime;
		cost = 400;
	}
}

Tower::~Tower()
{
	o_Model.~Model();
	for (int i = 0; i < o_Texture.size(); i++) {
		o_Texture.at(i).~Texture();
	}
}

void Tower::Build(int x, int y)//Set Tower Texture position based on Tile Num
{
	o_position.x = x * 0.15f;
	o_position.y = y * -0.2f;
	o_position.z = 0;

	towerPos.x = x * 0.15f;
	towerPos.y = y * -0.2f;

	Scale.SetIdentity();
	Rotation.SetIdentity();
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;
}

void Tower::Upgrade()//Upgrade price = 1/2 cost, each upgrade increases cost by half of its original value
{ 
	if (upgrade == 0) {
		o_Texture.at(0) = o_Texture.at(1);
		cost += cost / 2;
		if (towerType == 0)
		{
			damage += 5;
			range += 0.05f;
		}

		if (towerType == 1)
		{
			damage += 10;
			range += 0.1f;
		}
	}

	if (upgrade == 1) {
		o_Texture.at(0) = o_Texture.at(2);
		cost += cost / 2;
		if (towerType == 0)
		{
			damage += 5;
			range += 0.05f;
		}

		if (towerType == 1)
		{
			damage += 10;
			range += 0.1f;
		}
	}

	if (upgrade <=1) upgrade++;

	//cout << upgrade << endl;
	if (upgrade>=2) { //cout << "Max Upgrade!" << endl;
		return;
	}
}

void Tower::Update()
{
	
}

float Tower::CalculateDistanceToEnemies(Enemies *e)//must Enemies* or White Screen
{
	towerPos.x = o_position.x ;
	towerPos.y = o_position.y ;
	float deltaX = towerPos.x - (e->o_position.x);
	float deltaY = towerPos.y - (e->o_position.y);

	float distance = sqrtf(powf(deltaX, 2.0f) + powf(deltaY, 2.0f));
	return distance;
}

void Tower::AddEnemiesInRange(vector <Enemies*> enemyWave)//check if enemies in firing range then add them to enemiesInRange
{
	for (int i = 0; i < enemyWave.size(); i++)
	{
		float distance = CalculateDistanceToEnemies(enemyWave.at(i));
		if (distance <= range) {
			enemiesInRange.push_back(enemyWave.at(i));
			//cout << enemiesInRange.at(i)->o_position.x << endl;
		}
	}
}

void Tower::RemoveEnemiesOutOfRange()//Remove enemies moved out of range and update target
{
	if (enemiesInRange.size()!=0)
	{
		for (int i = 0; i < enemiesInRange.size(); i++)
		{
			float distance = CalculateDistanceToEnemies(enemiesInRange.at(i));

			if (distance > range || !enemiesInRange.at(i)->alive) {
				enemiesInRange.erase(enemiesInRange.begin() + i);
				//cout << "Out!" << endl;
			}
		}
	}

	SetTarget();
}

void Tower::Shoot()//leak here
{
	if (enemiesInRange.size() != 0 && currentTarget!=nullptr) {		
		if (CheckReload()) {
			Projectile *p = new Projectile(towerType, o_shaders);//will leak if !bullet->reachedTarget
			p->target = currentTarget;
			p->InitObject();
			if (towerType != 2) p->SetFiringLocation(o_position.x, o_position.y);
			if (towerType == 2) p->SetFiringLocation(currentTarget->o_position.x - 0.05f, currentTarget->o_position.y + 0.15f);
			projectileOnScreen.push_back(p);
		}
		
		
		for (int i = 0; i < projectileOnScreen.size(); i++) {
			if (projectileOnScreen.at(i)->target == nullptr
				|| projectileOnScreen.at(i)->target->alive == false) {
				//cout << "nul" << endl;
				projectileOnScreen.at(i)->nullified = true;
			}

			if (projectileOnScreen.at(i)->reachedTarget==false && !projectileOnScreen.at(i)->nullified)
			{
				projectileOnScreen.at(i)->DrawObject();
				projectileOnScreen.at(i)->CheckReachedTarget();
			}

			if (projectileOnScreen.at(i)->reachedTarget == true) {
				projectileOnScreen.at(i)->nullified = true;
				currentTarget->currentHP -= damage;
				if (towerType == 2) currentTarget->slowed = true;

				if (towerType == 3) {
					int range = 100 - 1 + 1;
					int effect = rand() % range + 1;
					if (effect >= 97 - upgrade) {
						currentTarget->currentHP -= 100 * (upgrade + 1);
						cout << "POW!" << endl;
					}
					if (effect >= 1 && effect <= 10 + upgrade * 5) {
						currentTarget->currentHP -= damage;
						currentTarget->slowed = true;
						cout << "SLOW!" << endl;
					}
				}
			}

			if (projectileOnScreen.at(i)->nullified==true)
			{
				//cout << "Nulled ";
				delete projectileOnScreen.at(i);
				projectileOnScreen.erase(projectileOnScreen.begin() + i);
			}
		}
	}
}

void Tower::SetTarget()
{
	if (!enemiesInRange.empty()) {
		currentTarget = enemiesInRange.front();
	}

	if (currentTarget != nullptr && enemiesInRange.empty()) currentTarget = nullptr;
}

bool Tower::CheckReload()
{
	if (towerType != 4) {
		timeSinceLastShot += reloadSpeed;
		if (timeSinceLastShot >= reloadTime) {
			timeSinceLastShot = 0.0f;
			return true;
		}
		else return false;
	}

	/*if (towerType == 3) {
		timeSinceLastShot += reloadSpeed;
		if (timeSinceLastShot >= 6.0f) {
			timeSinceLastShot = 0.0f;
			return false;
		}

		if (timeSinceLastShot >= reloadTime && timeSinceLastShot>=5.0f) {
			return true;
		}

		else return false;
	}*/
}