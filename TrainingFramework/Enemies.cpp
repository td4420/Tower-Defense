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

		std::cout << enemyVertices[i].pos.x << " " << enemyVertices[i].pos.y << " " << enemyVertices[i].pos.z << std::endl;
	}
}

Enemies::Enemies(Shaders shader, int maxHP, float speed, int reward)
{
	enemyShaders = shader;
	o_shaders = shader;

	this->maxHP = maxHP;
	this->currentHP = this->maxHP;
	this->movementSpeed = speed;
	this->reward = reward;

	o_Model = Model("../Resources/model.nfg");
	o_Texture.push_back(Texture("../Resources/enemyFacingRight.tga"));
	Scale.SetIdentity();
	//Rx.SetRotationX(3.14f);
	//Ry.SetRotationY(0);
	//Rz.SetRotationZ(0);
	//Rotation = Rz * Rx * Ry;
	Rotation.SetIdentity();
	Translation.SetIdentity();
	MVP = Scale * Rotation * Translation;

	/*enemyVertices[0].pos.x = -1.0f;  enemyVertices[0].pos.y = 1.0f; enemyVertices[0].pos.z = -0.1f;
	enemyVertices[1].pos.x = -0.85f; enemyVertices[1].pos.y = 1.0f; enemyVertices[1].pos.z = -0.1f;
	enemyVertices[2].pos.x = -0.85f; enemyVertices[2].pos.y = 0.8f; enemyVertices[2].pos.z = -0.1f;
	enemyVertices[3].pos.x = -1.0f;  enemyVertices[3].pos.y = 0.8f; enemyVertices[3].pos.z = -0.1f;

	enemyVertices[0].coords.x = 0.0f;	enemyVertices[0].coords.y = 0.0f;
	enemyVertices[1].coords.x = 1.0f;	enemyVertices[1].coords.y = 0.0f;
	enemyVertices[2].coords.x = 1.0f;	enemyVertices[2].coords.y = 1.0f;
	enemyVertices[3].coords.x = 0.0f;	enemyVertices[3].coords.y = 1.0f;*/

	/*for (int i = 0; i < 4; i++) {

		cout << enemyVertices[i].pos.x << " " << enemyVertices[i].pos.y << " " << enemyVertices[i].pos.z << endl;
		cout << enemyVertices[i].coords.x << " " << enemyVertices[i].coords.y << endl;
	}*/
}

//Enemies::Enemies(Shaders shader,int maxHP, float speed, int reward, Tile spawner)
//{
//	enemyShaders = shader;
//
//	this->maxHP = maxHP;
//	this->currentHP = this->maxHP;
//	this->movementSpeed = speed;
//	this->reward = reward;
//
//	//spawnTile = spawner;
//	//enemyTexture = Texture("../Resources/enemy.tga");
//	//this->enemyTexture.Init();
//
//	for (int i = 0; i < 4; i++) {
//		enemyVertices[i].pos.x = spawner.tileVertices[i].pos.x;
//		enemyVertices[i].pos.y = spawner.tileVertices[i].pos.y;
//		enemyVertices[i].pos.z = spawner.tileVertices[i].pos.z;
//
//		enemyVertices[i].coords.x = spawner.tileVertices[i].coords.x;
//		enemyVertices[i].coords.y = spawner.tileVertices[i].coords.y;
//
//		std::cout << enemyVertices[i].pos.x << " " << enemyVertices[i].pos.y << " " << enemyVertices[i].pos.z << std::endl;
//	}
//
//}

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

	//cout << "Binded" << endl;
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

	//std::cout << enemyVertices[0].pos.x << " " << enemyVertices[0].pos.y << " " << enemyVertices[0].pos.z << std::endl;
}

void Enemies::Update() 
{
	o_position.x += movementSpeed;
	o_position.y = 0;
	o_position.z = 0;
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;

	DrawObject();
}

void Enemies::Kill()
{
	if (reachedExit == true);

	//if (currentHP <= 0) ~Object();
}