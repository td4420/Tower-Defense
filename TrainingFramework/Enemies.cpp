#include "stdafx.h"
#include "Enemies.h"
#include "Tile.h"
#include "Shaders.h"

Enemies::Enemies()
{
	o_Model = new Model("../Resources/model.txt");
	o_Texture.push_back(new Texture("../Resources/enemy.tga"));

	Scale.SetIdentity();
	Translation.SetIdentity();
	Rotation.SetIdentity();
}

Enemies::Enemies(int type)
{
	o_Model = new Model("../Resources/model.nfg");
	Scale.SetIdentity();
	Rotation.SetIdentity();
	Translation.SetIdentity();
	MVP = Scale * Rotation * Translation;
	slowTime = 0.0f;
	enemyType = type;
	animation.Init();

	if (type == 1)
	{
		o_Texture.push_back(new Texture("../Resources/enemy.tga"));
		maxHP = 100;
		currentHP = maxHP;
		movementSpeed = 0.1f;
		fixedSpeed = 0.1f;
		reward = 40;
		for (int i = 0; i < animation.normalMoveLeft.size(); i++)
		{
			o_Texture.push_back(animation.normalMoveLeft.at(i));
		}
		for (int j = 0; j < animation.normalMoveRight.size(); j++)
		{
			o_Texture.push_back(animation.normalMoveRight.at(j));
		}
	}

	if (type == 2)
	{
		o_Texture.push_back(new Texture("../ResourcesPacket/Textures/fastEnemy.tga"));
		maxHP = 70;
		currentHP = maxHP;
		movementSpeed = 0.2f;//0.005f;
		fixedSpeed = 0.2f;//0.005f;
		reward = 25;
		for (int i = 0; i < animation.fastMoveLeft.size(); i++)
		{
			o_Texture.push_back(animation.fastMoveLeft.at(i));
		}
		for (int j = 0; j < animation.fastMoveRight.size(); j++)
		{
			o_Texture.push_back(animation.fastMoveRight.at(j));
		}
	}

	if (type == 3)
	{
		o_Texture.push_back(new Texture("../ResourcesPacket/Textures/tanker.tga"));
		maxHP = 300;
		currentHP = maxHP;
		movementSpeed = 0.09f;
		fixedSpeed = 0.09f;
		reward = 100;

	}

	if (type == 4)
	{
		o_Texture.push_back(new Texture("../ResourcesPacket/Textures/tanker.tga"));
		maxHP = 300;
		currentHP = maxHP;
		movementSpeed = 0.09f; //0.001f;
		fixedSpeed = 0.09f;//0.001f;
		reward = 100;
		for (int i = 0; i < animation.tankMoveLeft.size(); i++)
		{
			o_Texture.push_back(animation.tankMoveLeft.at(i));
		}
		for (int j = 0; j < animation.tankMoveRight.size(); j++)
		{
			o_Texture.push_back(animation.tankMoveRight.at(j));
		}
	}
	//HP->moveSpeed = movementSpeed;
	//HP->init();
}

Enemies::Enemies(Enemies* e)
{
	maxHP = e->maxHP;
	cout << "jafajf";
	currentHP = this->maxHP;
	movementSpeed = e->movementSpeed;
	fixedSpeed = e->fixedSpeed;
	reward = e->reward;
	enemyType = e->enemyType;
	o_Model = e->o_Model;
	for (int i = 0; i < e->o_Texture.size(); i++) {
		o_Texture.push_back(e->o_Texture.at(i));
	}
}

Enemies::~Enemies()
{
}

void Enemies::MoveToLeft(float deltaTime)
{
	float deltaX = o_position.x - locationX * 0.15;
	if (deltaX <= -0.15)
	{
		lastLocationX = locationX;
		lastLocationY = locationY;
		locationX--;
		step++;
		return;
	}
	o_position.x -= movementSpeed * deltaTime;
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;

}
void Enemies::MoveToRight(float deltaTime)
{

	float deltaX = o_position.x - locationX * 0.15;
	if (deltaX >= 0.15)
	{
		lastLocationX = locationX;
		lastLocationY = locationY;
		locationX++;
		step++;
		return;
	}
	o_position.x += movementSpeed * deltaTime;
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;

}

void Enemies::MoveDown(float deltaTime)
{
	float deltaY = -o_position.y - locationY * 0.2;
	if (deltaY >= 0.2)
	{
		lastLocationX = locationX;
		lastLocationY = locationY;
		locationY++;
		step++;
		return;
	}
	o_position.y -= movementSpeed * deltaTime;
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;

}

void Enemies::MoveUp(float deltaTime)
{
	float deltaY = -o_position.y - locationY * 0.2;
	if (deltaY <= -0.2)
	{
		lastLocationX = locationX;
		lastLocationY = locationY;
		locationY--;
		step++;
		return;
	}
	o_position.y += movementSpeed * deltaTime;
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;

}

void Enemies::MoveEnemies(float deltaTime, int NumMap[7][8])
{
	int temp;
	if (enemyType == 1) temp = animation.normalMoveLeft.size() + 1;
	if (enemyType == 2) temp = animation.fastMoveLeft.size() + 1;
	if (enemyType == 3 || enemyType == 4) temp = animation.tankMoveLeft.size() + 1;
	/*int NumMap[7][8] =
	{
		1,1,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,1,0,
		0,1,1,1,1,1,1,0,
		0,1,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1
	};*/
	if ((locationX - 1 != lastLocationX) && // To not move back
		locationX > 0 && NumMap[locationY][locationX - 1] == 1)  // Check if can move
	{
		o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveLeft(enemyType) + 1);
		toLeft = true;
		MoveToLeft(deltaTime);
		return;
	}
	if ((locationX + 1 != lastLocationX) &&  //To not move back
		locationX < 7 && NumMap[locationY][locationX + 1] == 1) // Check if can move
	{
		o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveRight(enemyType) + temp);
		toLeft = false;
		MoveToRight(deltaTime);
		return;
	}
	if ((locationY - 1 != lastLocationY) && // To not move back
		locationY > 0 && NumMap[locationY - 1][locationX] == 1)  // Check if can move
	{
		if (!toLeft) o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveRight(enemyType) + temp);
		else o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveLeft(enemyType) + 1);
		MoveUp(deltaTime);
		return;
	}
	if ((locationY + 1 != lastLocationY) && // To not move back
		locationY < 6 && NumMap[locationY + 1][locationX] == 1)  // Check if can move
	{
		if (!toLeft) o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveRight(enemyType) + temp);
		else o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveLeft(enemyType) + 1);
		MoveDown(deltaTime);
		return;
	}
}

void Enemies::Update(float deltaTime, int NumMap[7][8])
{
	//cout << "X: " << (o_position.x + 0.075f) << " Y: " << (o_position.y - 0.1f) << endl;
	CheckSlowed();
	MoveEnemies(deltaTime, NumMap);

	/*strHP = std::to_string(currentHP);
	charHp = strHP.c_str();
	HP->text = charHp;*/

	if (currentHP <= 0)
	{
		alive = false;
	}
}

void Enemies::CheckSlowed()
{
	if (slowed && slowTime <= 0.1f)
	{
		slowTime = 7.1f;
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
void Enemies::Reset()
{
	alive = true;
	reachedExit = false;
	o_position.x = 0; o_position.y = 0;
	locationX = 0; locationY = 0; lastLocationX = 0; lastLocationY = 0;
	if (enemyType == 1)
	{
		maxHP = 100;
		currentHP = maxHP;
	}
	if (enemyType == 2)
	{
		maxHP = 70;
		currentHP = 70;
	}
	if (enemyType == 4)
	{
		maxHP = 300;
		currentHP = 300;
	}
	Scale.SetIdentity();
	Rotation.SetIdentity();
	Translation.SetIdentity();
	MVP = Scale * Rotation * Translation;
}

void Enemies::CleanUp()
{
	delete o_Model;
	for (int i = 0; i < o_Texture.size(); i++)
	{
		delete o_Texture.at(i);
	}
}