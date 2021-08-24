#pragma once
#include "Object.h"
#include "Tile.h"
#include "Texture.h"
#include "Shaders.h"
#include "Vertex.h"
#include "Animation.h"
class Enemies :
	public Object
{
public:
	/*enum EnemyType
	{
		NORMAL, FAST, TANK
	};*/
	int enemyType;//1:normal, 2:fast, 3:tank

	Vector2 enemyPos;
	int locationX = 0, locationY = 0;
	int lastLocationX = 0, lastLocationY = 0;
	int maxHP = 60;
	int currentHP = 60;

	float movementSpeed = 0.001f;
	float fixedSpeed = movementSpeed;
	int reward = 3;

	float slowTime = 0.0f;

	bool alive = true;
	bool slowed = false;
	bool reachedExit = false;


	bool toLeft = false; //Check the last step is go to left or right
	Animation animation;

	GLuint enemyVBO;
	//GLuint enemyIBO;

	Enemies();
	Enemies(int type);
	Enemies(Enemies* e);
	Enemies(Shaders myShaders, int maxHP, float speed, int reward);
	Enemies(Shaders myShaders, int maxHP, float speed, int reward, Tile spawner);
	~Enemies();

	//void Bind();
	void Reset();
	void MoveEnemies();
	void MoveToLeft();
	void MoveToRight();
	void MoveUp();
	void MoveDown();
	void Draw();
	void Update();
	void Kill();
	void CheckSlowed();
};