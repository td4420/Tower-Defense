#include "stdafx.h"
#include "Projectile.h"
#include <cmath>

Projectile::Projectile()
{
	o_Model = Model("../Resources/modelProjectile.nfg");
	o_Texture.push_back("../ResourcesPacket/Textures/machineGunTowerProjectile.tga");
}

Projectile::Projectile(Projectile* p)
{
	o_Model = p->o_Model;
	o_Texture.push_back(p->o_Texture.at(0));
}

Projectile::Projectile(int type, Shaders shaders)
{
	projectileType = type;
	o_Model = Model("../Resources/modelProjectile.nfg");
	o_Texture.push_back(Texture("../ResourcesPacket/Textures/bullet.tga"));
	o_shaders = shaders;

	movementSpeed = 0.01f;
	Scale.SetIdentity();
	Rotation.SetIdentity();
}

Projectile::~Projectile()
{
	o_Model.~Model();
	for (int i = 0; i < o_Texture.size(); i++) {
		o_Texture.at(i).~Texture();
	}
}

void Projectile::SetFiringLocation(float x, float y)
{
	o_position.x = x;
	o_position.y = y;
	o_position.z = 0.0f;

	Translation.SetTranslation(o_position);
	Scale.SetIdentity();
	Rotation.SetIdentity();
	MVP = Scale * Rotation * Translation;
}

float Projectile::CalculateDistanceToTarget()
{
	float deltaX = o_position.x - target->o_position.x;
	float deltaY = o_position.y - target->o_position.y;
	float distance = sqrtf(powf(deltaX, 2.0f) + powf(deltaY, 2.0f));
	return distance;
}

void Projectile::CheckReachedTarget()
{
	if (CalculateDistanceToTarget() <= 0.1f)
	{
		//cout << "Hit!" << endl;
		reachedTarget = true;
		
	}
}

float Projectile::GetAngleToEnemies()
{
	float deltaX = target->o_position.x - o_position.x;
	float deltaY = target->o_position.y - o_position.y;
	float angle = atan2f(deltaY, deltaX);
	
	return angle;
}

void Projectile::Move(float angle)
{
	if (!moving) {
		firingAngle = angle;
	}

	moving = true;
	o_position.x += movementSpeed * cosf(firingAngle);
	o_position.y += movementSpeed * sinf(firingAngle);
	o_position.z = 0.0f;
	//cout << o_position.x << " " << o_position.y << endl;

	Scale.SetIdentity();
	Rotation.SetIdentity();
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;
}
