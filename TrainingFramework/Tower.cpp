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
	upgrade = 0;
	if (towerType == 0)
	{
		o_Model = Model("../Resources/model.nfg");
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/archerTower.tga"));
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/archerTower2.tga"));
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/archerTower3.tga"));
		damage = 5;
		range = 0.3f;
		reloadTime = 0;
	}

	if (towerType == 1)
	{
		o_Model = Model("../Resources/model.nfg");
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/mortarTower.tga"));
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/mortarTower2.tga"));
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/mortarTower3.tga"));
		damage = 20;
		range = 0.5f;
		reloadTime = 0;
	}
}

//Tower::~Tower()
//{
//	o_Model.~Model();
//	for (int i = 0; i < o_Texture.size(); i++) {
//		o_Texture.at(i).~Texture();
//	}
//}

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
		upgrade = 1;
		o_Texture.at(0) = o_Texture.at(1);
		cost += cost / 2;
		if (towerType == 0)
		{
			damage += 5;
			range += 0;
		}

		if (towerType == 1)
		{
			damage += 10;
		}
	}

	if (upgrade == 1) {
		upgrade = 2;
		o_Texture.at(0) = o_Texture.at(2);
		cost += cost / 2;
		if (towerType == 0)
		{
			damage += 5;
			range += 0;
		}

		if (towerType == 1)
		{
			damage += 10;
		}
	}

	if (upgrade>=2) { //cout << "Max Upgrade!" << endl;
		return;
	}
	//cout << upgrade << endl;
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

	//return 0;
}

void Tower::AddEnemiesInRange(vector <Enemies*> enemyWave)//check if enemies in firing range then add them to enemiesInRange
{
	for (int i = 0; i < enemyWave.size(); i++)
	{
		float distance = CalculateDistanceToEnemies(enemyWave.at(i));
		if (distance <= range) {
			enemiesInRange.push_back(enemyWave.at(i));
			//cout << enemiesInRange.at(i)->o_position.x << endl;
			canAttack = true;
		}
		//cout << distance << endl;
	}
	//SetTarget();
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

	//if (enemiesInRange.size() == 0) canAttack = false;
}

void Tower::Shoot()//leak here
{
	if (projectileOnScreen.size() != 0 && enemiesInRange.size() == 0)
	{
		projectileOnScreen.at(0)->~Projectile();
		projectileOnScreen.clear();
	}

	if (enemiesInRange.size() != 0 && currentTarget!=nullptr) {
		
		if (projectileOnScreen.size() == 0) {
			Projectile *p = new Projectile(towerType, o_shaders);//1 leak per shot
			p->target = currentTarget;
			p->InitObject();
			p->SetFiringLocation(o_position.x, o_position.y);
			projectileOnScreen.push_back(p);
		}
		
		
		for (int i = 0; i < projectileOnScreen.size(); i++) {
			if (projectileOnScreen.at(i)->reachedTarget == true) {
				currentTarget->currentHP -= damage;
				projectileOnScreen.at(i)->~Projectile();//must have or lots of leak :V
				projectileOnScreen.clear();
				//projectileOnScreen.erase(projectileOnScreen.begin()+i);// without this line causes null pointer deletion?
			}
			//cout << currentTarget->currentHP << endl;

			if (projectileOnScreen.size() != 0) {
				if (projectileOnScreen.at(i)->reachedTarget == false) {
					projectileOnScreen.at(i)->DrawObject();
					projectileOnScreen.at(i)->CheckReachedTarget();
				}
			}
		}
	}
}

void Tower::SetTarget()
{
	if (!enemiesInRange.empty()) {
		currentTarget = enemiesInRange.front();
		//cout << "Atk ";
	}

	//if (currentTarget!=nullptr && !currentTarget->alive && !enemiesInRange.empty()) currentTarget = enemiesInRange.front();

	if (currentTarget != nullptr && enemiesInRange.empty()) currentTarget = nullptr;
}