#include "stdafx.h"
#include "Projectile.h"
#include <cmath>

Projectile::Projectile()
{

}

Projectile::Projectile(Projectile* p)
{
	o_Model = p->o_Model;
	o_Texture.push_back(p->o_Texture.at(0));
}

Projectile::Projectile(int type)
{
	projectileType = type;
	o_Model = new Model("../Resources/modelProjectile.nfg");
	nullified = false;
	target = nullptr;

	if (type == 0)
	{
		o_Texture.push_back(new Texture("../ResourcesPacket/Textures/fireBullet.tga"));
	}

	if (type == 1)
	{
		o_Texture.push_back(new Texture ("../ResourcesPacket/Textures/mortarBullet.tga"));
	}
	if (type == 2)  o_Texture.push_back(new Texture ("../ResourcesPacket/Textures/thunderBullet.tga"));

	if (type == 3) o_Texture.push_back(new Texture ("../ResourcesPacket/Textures/bullet.tga"));

	//if (type == 4) o_Texture.push_back(new Texture "../ResourcesPacket/Textures/bullet.tga");

	movementSpeed = 0.02f;
	Scale.SetIdentity();
	Rotation.SetIdentity();
}

Projectile::Projectile(int type, Shaders shaders)
{
	projectileType = type;
	o_Model = new Model("../Resources/modelProjectile.nfg");
	nullified = false;
	target = nullptr;

	if (type == 0)
	{
		o_Texture.push_back(new Texture ("../ResourcesPacket/Textures/fireBullet.tga"));
	}

	if (type == 1)
	{
		o_Texture.push_back(new Texture ("../ResourcesPacket/Textures/mortarBullet.tga"));
	}
	if (type == 2)  o_Texture.push_back(new Texture ("../ResourcesPacket/Textures/thunderBullet.tga"));

	if (type == 3) o_Texture.push_back(new Texture ("../ResourcesPacket/Textures/bullet.tga"));
	

	movementSpeed = 0.025f;
	Scale.SetIdentity();
	Rotation.SetIdentity();
}

Projectile::~Projectile()
{

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
		reachedTarget = true;
	}
}

void Projectile::Bounce(vector <Enemies*> enemyWave)//later
{
	for (int i = 0; i < enemyWave.size(); i++) {

	}
}

float Projectile::GetAngleToEnemies()
{
	//if (target != nullptr) {
		float deltaX = target->o_position.x - o_position.x;
		float deltaY = target->o_position.y - o_position.y;
		float angle = atan2f(deltaY, deltaX);

		return angle;
	//}
}

void Projectile::Move(float angle)
{
	//cout << angle << endl;
	//firingAngle = angle;

	o_position.x += movementSpeed * cosf(angle);
	o_position.y += movementSpeed * sinf(angle);
	o_position.z = 0.0f;

	Scale.SetIdentity();
	Rotation.SetIdentity();
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;
}

void Projectile::Reset()
{
	reachedTarget = false;
	nullified = false;
	target = nullptr;
}