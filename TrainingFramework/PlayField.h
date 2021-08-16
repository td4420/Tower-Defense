#pragma once
#include <vector>
#include "Tile.h"
#include "Shaders.h"
#include "Enemies.h"
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

	int enemyWaveEasy[5][10] =
	{
		1,1,1,1,1,1,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,
		1,2,1,2,1,2,1,2,1,2,
		0,0,0,0,5,0,0,0,0,0,
		1,0,0,1,0,4,0,2,1,4
	};

	int NumMapNormal[7][8] = {
		1,1,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,1,0,
		0,0,0,1,1,1,1,0,
		0,0,0,1,0,0,0,0,
		0,0,0,1,1,1,1,1
	};

	int NumMap[7][8];

	Tile TileMap[7][8];
	vector <Enemies*> tempEnemyWave;
	vector <Enemies*> enemyWave;
	//std::vector <int*> NumMap;
	const int waveLength = 10;
	const int mapHeight = 7;
	const int mapWidth = 8;
	const float spawnTime = 10.0f;

	int countWaveEndInit = 0;
	bool waveEnd = true;
	float timeSinceLastSpawn = 10.0f;
	int waveNum = 4;//save the number of waves in a lv;
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

