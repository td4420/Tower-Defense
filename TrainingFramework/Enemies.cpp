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
	if (type == 1)
	{
		maxHP = 60;
		currentHP = maxHP;
		movementSpeed = 0.001f;
		reward = 10;
	}

	if (type == 2)
	{
		maxHP = 30;
		currentHP = maxHP;
		movementSpeed = 0.002f;
		reward = 12;
	}

	if (type == 3)
	{
		maxHP = 100;
		currentHP = maxHP;
		movementSpeed = 0.0005f;
		reward = 20;
	}
}

Enemies::Enemies(Enemies* e)
{
	maxHP = e->maxHP;
	currentHP = maxHP;
	movementSpeed = e->movementSpeed;
	reward = this->reward;

	for (int i = 0; i < 4; i++) {
		enemyVertices[i].pos.x = e->enemyVertices[i].pos.x;
		enemyVertices[i].pos.y = e->enemyVertices[i].pos.y;
		enemyVertices[i].pos.z = e->enemyVertices[i].pos.z;

		enemyVertices[i].coords.x = e->enemyVertices[i].coords.x;
		enemyVertices[i].coords.y = e->enemyVertices[i].coords.y;
	}
}

Enemies::Enemies(Shaders shader, int maxHP, float speed, int reward)
{
	animation.InitEnemies();
	enemyShaders = shader;
	o_shaders = shader;

	this->maxHP = maxHP;
	this->currentHP = this->maxHP;
	this->movementSpeed = speed;
	this->reward = reward;
	o_Model = Model("../Resources/model.nfg");
	o_Texture.push_back(Texture("../ResourcesPacket/AnimationMove/Left/2_enemies_1_walk_001.tga"));
	Scale.SetIdentity();
	Rotation.SetIdentity();
	Translation.SetIdentity();
	MVP = Scale * Rotation * Translation;
	for (int i = 0; i < animation.animationMoveLeft.size(); i++)
	{
		o_Texture.push_back(animation.animationMoveLeft.at(i));
	}
	for (int j = 0; j < animation.animationMoveRight.size(); j++)
	{
		o_Texture.push_back(animation.animationMoveRight.at(j));
	}
}

void Enemies::SetShaders(Shaders shader)
{
	enemyShaders = shader;
}

void Enemies::SetSpawner(Tile spawner)
{
	for (int i = 0; i < 4; i++) {
		enemyVertices[i].pos.x = spawner.tileVertices[i].pos.x;
		enemyVertices[i].pos.y = spawner.tileVertices[i].pos.y;
		enemyVertices[i].pos.z = spawner.tileVertices[i].pos.z;

		enemyVertices[i].coords.x = spawner.tileVertices[i].coords.x;
		enemyVertices[i].coords.y = spawner.tileVertices[i].coords.y;
	}
}

void Enemies::Bind() {
	glGenBuffers(1, &enemyVBO);
	glBindBuffer(GL_ARRAY_BUFFER, enemyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(enemyVertices), enemyVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Enemies::Draw()
{
	glUseProgram(o_shaders.program);
	glBindTexture(GL_TEXTURE_2D, enemyTexture.mTextureId);
	glBindBuffer(GL_ARRAY_BUFFER, enemyVBO);

	if (o_shaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(o_shaders.positionAttribute);
		glVertexAttribPointer(o_shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (o_shaders.uvAttribute != -1)
	{
		glUniform1i(enemyShaders.uvAttribute, 0);
		glEnableVertexAttribArray(o_shaders.uvAttribute);
		glVertexAttribPointer(o_shaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Vector3)));

	}

	GLushort indices[]{ 0,2,3 };
	GLushort in[]{ 0,2,3 };

	glUniformMatrix4fv(o_shaders.u_MVP, 1, GL_FALSE, *MVP.m);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, &in);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, &indices);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
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
		0,0,0,1,1,1,1,0,
		0,0,0,1,0,0,0,0,
		0,0,0,1,1,1,1,1
	};
	if ((locationX - 1 != lastLocationX) && // To not move back
		locationX > 0 && NumMap[locationY][locationX-1] == 1)  // Check if can move
	{
		o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveLeft() + 1);
		toLeft = true;
		MoveToLeft();
		return;
	}
	if ((locationX + 1 != lastLocationX) &&  //To not move back
		locationX < 7 && NumMap[locationY][locationX+1] == 1) // Check if can move
	{
		o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveRight() + animation.animationMoveLeft.size() + 1);
		toLeft = false;
		MoveToRight();
		return;
	}
	if ((locationY - 1 != lastLocationY) && // To not move back
		locationY > 0 && NumMap[locationY-1][locationX] == 1)  // Check if can move
	{
		if(!toLeft) o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveRight() + animation.animationMoveLeft.size() + 1);
		else o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveLeft() + 1);
		MoveUp();
		return;
	}
	if ((locationY + 1 != lastLocationY) && // To not move back
		locationY < 6 && NumMap[locationY+1][locationX] == 1)  // Check if can move
	{
		if (!toLeft) o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveRight() + animation.animationMoveLeft.size() + 1);
		else o_Texture.at(0) = o_Texture.at(animation.GetAnimationMoveLeft() + 1);
		MoveDown();
		return;
	}
}

void Enemies::Update() 
{
	MoveEnemies();
}

void Enemies::Kill()
{
	if (reachedExit == true);

	//if (currentHP <= 0) ~Object();
}