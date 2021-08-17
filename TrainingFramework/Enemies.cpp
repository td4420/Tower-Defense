#include "stdafx.h"
#include "Enemies.h"
#include "Tile.h"
#include "Shaders.h"

Enemies::Enemies()
{
	o_Model = Model("../Resources/model.txt");
	o_Texture.push_back(Texture("../Resources/enemy.tga"));

	Scale.SetIdentity();
	Translation.SetIdentity();
	Rotation.SetIdentity();
}

Enemies::Enemies(int type)
{
	o_Model = Model("../Resources/model.nfg");
	Scale.SetIdentity();
	Rotation.SetIdentity();
	Translation.SetIdentity();
	MVP = Scale * Rotation * Translation;
	slowTime = 0.0f;

	if (type == 1)
	{
		o_Texture.push_back(Texture("../Resources/enemy.tga"));
		maxHP = 70;
		currentHP = maxHP;
		movementSpeed = 0.003f;
		fixedSpeed = 0.002f;
		reward = 30;
	}

	if (type == 2)
	{
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/fastEnemy.tga"));
		maxHP = 50;
		currentHP = maxHP;
		movementSpeed = 0.005f;
		fixedSpeed = 0.005f;
		reward = 25;
	}

	if (type == 3)
	{
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/tanker.tga"));
		maxHP = 300;
		currentHP = maxHP;
		movementSpeed = 0.001f;
		fixedSpeed = 0.001f;
		reward = 100;
	}

	if (type == 4)
	{
		o_Texture.push_back(Texture("../ResourcesPacket/Textures/tanker.tga"));
		maxHP = 300;
		currentHP = maxHP;
		movementSpeed = 0.001f;
		fixedSpeed = 0.001f;
		reward = 100;
	}
}

Enemies::Enemies(Enemies* e)
{
	maxHP = e->maxHP;
	currentHP = this->maxHP;
	movementSpeed = e->movementSpeed;
	fixedSpeed = e->fixedSpeed;
	reward = e->reward;

	o_Model = e->o_Model;
	for (int i = 0; i < e->o_Texture.size(); i++) {
		o_Texture.push_back(e->o_Texture.at(i));
	}
}

Enemies::Enemies(Shaders shader, int maxHP, float speed, int reward)
{
	o_shaders = shader;

	this->maxHP = maxHP;
	this->currentHP = maxHP;
	this->movementSpeed = speed;
	this->reward = reward;
	o_Model = Model("../Resources/model.nfg");
	o_Texture.push_back(Texture("../Resources/enemy.tga"));
	Scale.SetIdentity();
	Rotation.SetIdentity();
	Translation.SetIdentity();
	MVP = Scale * Rotation * Translation;

}

Enemies::~Enemies()
{
	o_Model.~Model();
	for (int i = 0; i < o_Texture.size(); i++)
	{
		o_Texture.at(i).~Texture();
	}
}



void Enemies::MoveToLeft()
{
	float deltaX = o_position.x - locationX * 0.15;
	if (deltaX <= -0.15)
	{
		lastLocationX = locationX;
		lastLocationY = locationY;
		locationX--;
		return;
	}
	o_position.x -= movementSpeed;
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;

}
void Enemies::MoveToRight()
{
	
	float deltaX = o_position.x - locationX*0.15;
	if (deltaX >= 0.15)
	{
		lastLocationX = locationX;
		lastLocationY = locationY;
		locationX++;
		return;
	}
	o_position.x += movementSpeed;
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;

}

void Enemies::MoveDown()
{
	float deltaY = -o_position.y - locationY * 0.2;
	if (deltaY >= 0.2)
	{
		lastLocationX = locationX;
		lastLocationY = locationY;
		locationY++;
		return;
	}
	o_position.y -= movementSpeed;
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;

}

void Enemies::MoveUp()
{
	float deltaY = -o_position.y - locationY * 0.2;
	if (deltaY <= -0.2)
	{
		lastLocationX = locationX;
		lastLocationY = locationY;
		locationY--;
		return;
	}
	o_position.y += movementSpeed;
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;
	
}

void Enemies::MoveEnemies()
{
	int NumMap[7][8] =
	{
		1,1,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,1,0,
		0,1,1,1,1,1,1,0,
		0,1,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1
	};
	if ((locationX - 1 != lastLocationX) && // To not move back
		locationX > 0 && NumMap[locationY][locationX-1] == 1)  // Check if can move
	{
		MoveToLeft();
		return;
	}
	if ((locationX + 1 != lastLocationX) &&  //To not move back
		locationX < 6 && NumMap[locationY][locationX+1] == 1) // Check if can move
	{
		MoveToRight();
		return;
	}
	if ((locationY - 1 != lastLocationY) && // To not move back
		locationY > 0 && NumMap[locationY-1][locationX] == 1)  // Check if can move
	{
		MoveUp();
		return;
	}
	if ((locationY + 1 != lastLocationY) && // To not move back
		locationY < 7 && NumMap[locationY+1][locationX] == 1)  // Check if can move
	{
		MoveDown();
		return;
	}
}

void Enemies::Update() 
{
	//cout << "X: " << (o_position.x + 0.075f) << " Y: " << (o_position.y - 0.1f) << endl;
	CheckSlowed();
	
	MoveEnemies();
	if (currentHP <= 0)
	{
		alive = false;
	}
}

void Enemies::Kill()
{
	if (reachedExit == true);

	//if (currentHP <= 0) ~Object();
}

void Enemies::CheckSlowed()
{
	if (slowed && slowTime <= 0.1f)
	{
		slowTime = 6.1f;
		//slowed = false;
	}

	if (!slowed && slowTime <= 0.1f) {
		movementSpeed = fixedSpeed;
	}

	if (slowTime > 0.1f)
	{
		//cout << slowTime << " ";
		slowTime -= 0.1f;
		movementSpeed = movementSpeed * 0.95f;
		slowed = false;
	}
}