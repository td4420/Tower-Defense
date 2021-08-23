#pragma once
#include <vector>
#include "Tile.h"
#include "Shaders.h"
#include "Enemies.h"
#include "Tower.h"
class PlayField
{
public:
	const float disX = 0.15f;
	const float disY = 0.2f;

	int NumMapEasy[7][8] = {
		0,0,0,0,0,1,1,1,
		0,1,1,1,0,1,0,1,
		0,1,0,1,0,1,0,1,
		0,1,0,1,0,1,0,1,
		0,1,0,1,0,1,0,1,
		1,1,0,1,1,1,0,1,
		0,0,0,0,0,0,0,1
	};

	int enemyWaveEasy[10][10] =//used to init waves
	{
		1,1,1,1,1,1,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		0,2,0,2,0,2,0,2,0,0,
		1,2,0,1,2,0,1,2,0,0,
		0,0,0,0,4,0,0,0,0,0,
		1,0,0,1,0,4,0,0,1,2,
		2,2,2,2,2,2,2,2,2,2,
		1,2,1,2,1,2,1,4,1,4,
		1,2,4,1,2,4,1,2,4,4
	};

	int NumMapNormal[7][8] = //used to create TileMap
	{
		1,1,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,1,0,
		0,1,1,1,1,1,1,0,
		0,1,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1
	};

	int NumMap[7][8];

	Tile TileMap[7][8];
	Enemies* normal[10] = { new Enemies(1), new Enemies(1),new Enemies(1), new Enemies(1), new Enemies(1), new Enemies(1), new Enemies(1), new Enemies(1), new Enemies(1), new Enemies(1) }; //30
	Enemies* fast[10] = { new Enemies(2), new Enemies(2),new Enemies(2), new Enemies(2), new Enemies(2), new Enemies(2), new Enemies(2), new Enemies(2), new Enemies(2), new Enemies(2) }; //28
	Enemies* tank[10] = { new Enemies(4),new Enemies(4),new Enemies(4),new Enemies(4),new Enemies(4),new Enemies(4),new Enemies(4),new Enemies(4),new Enemies(4),new Enemies(4) }; //11
	int numberOfTank = 0, numberOfFast = 0, numberOfNormal = 0;
	vector <Enemies*> tempEnemyWave;
	vector <Enemies*> enemyWave;
	vector <Tower*> towerList;
	const int waveLength = 10;
	const int mapHeight = 7;
	const int mapWidth = 8;
	const float spawnTime = 15.0f;
	const int waveMax = 10;

	int countWaveEndInit = 0;
	bool waveEnd = true;
	bool nextWave = false;
	bool gameOver = false;
	float timeSinceLastSpawn = 15.0f;
	int waveNum = 0;//save the number of waves in a lv;
	Shaders myShaders;

	void Init(Shaders myShaders);
	void Draw();
	void InitEnemyWave();
	void SpawnEnemy();
	void CleanUp();
	void Update();
	bool CheckSpawnTime();

	PlayField();
	//~PlayField();
};