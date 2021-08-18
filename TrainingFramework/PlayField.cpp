#include "stdafx.h"
#include "PlayField.h"
#include "Tile.h"
#include "Shaders.h"
#include <vector>

PlayField::PlayField()
{

}

void PlayField::CleanUp()
{
	/*for (int i = 0; i < enemyWave.size(); i++) {
		delete enemyWave.at(i);
	}
	for (int i = 0; i < tempEnemyWave.size(); i++) {
		delete tempEnemyWave.at(i);
	}*/
}

void PlayField::Init(Shaders shaders)
{

	myShaders = shaders;
	int NumMap[7][8];


	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 8; j++) {
			NumMap[i][j] = NumMapNormal[i][j];
		}
	}

	float initX = -1.0f;
	float initY = 1.0f;

	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			float countX = disX * j;
			float countY = -disY * i;

			TileMap[i][j] = Tile(NumMap[i][j], i, j, initX + countX, initY + countY, shaders);
			TileMap[i][j].tileTexture.Init();

			TileMap[i][j].Bind();
		}
	}
	for (int i = 0; i < 10; i++)
	{
		normal[i]->o_shaders = myShaders;
		normal[i]->InitObject();
		fast[i]->o_shaders = myShaders;
		fast[i]->InitObject();
		tank[i]->o_shaders = myShaders;
		tank[i]->InitObject();
	}
}

void PlayField::Draw()
{
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			TileMap[i][j].Draw();
		}
	}
	if (gameOver == false) InitEnemyWave();
	SpawnEnemy();

	for (int i = 0; i < enemyWave.size(); i++) {
		enemyWave.at(i)->DrawObject();
	}
}

void PlayField::InitEnemyWave()
{
	if (waveEnd) {
		cout << "Wave lv: " << waveNum + 1 << endl;
		waveEnd = false;
		numberOfFast = 0; numberOfNormal = 0; numberOfTank = 0;
		for (int i = 0; i < 10; i++)
		{
			normal[i]->Reset();
			fast[i]->Reset();
			tank[i]->Reset();
		}
		for (int j = 0; j < waveLength; j++)
		{
			if (enemyWaveEasy[waveNum][j] == 1)
			{
				tempEnemyWave.push_back(normal[numberOfNormal]);
				numberOfNormal++;
			}
			if (enemyWaveEasy[waveNum][j] == 2)
			{
				tempEnemyWave.push_back(fast[numberOfFast]);
				numberOfFast++;
			}
			if (enemyWaveEasy[waveNum][j] == 4)
			{
				tempEnemyWave.push_back(tank[numberOfTank]);
				numberOfTank++;
			}
		}
		if (waveNum < waveMax) waveNum += 1;
	}
}

void PlayField::SpawnEnemy() {
	for (int i = 0; i < tempEnemyWave.size(); i++) {
		if (CheckSpawnTime()) {
			enemyWave.push_back(tempEnemyWave.at(i));
			tempEnemyWave.erase(tempEnemyWave.begin() + i);
		}
	}
}

bool PlayField::CheckSpawnTime()
{
	timeSinceLastSpawn += 0.1f;
	if (timeSinceLastSpawn >= spawnTime)
	{
		timeSinceLastSpawn = 0.0f;
		return true;
	}
	else return false;
}

void PlayField::Update()
{
	for (int i = 0; i < enemyWave.size(); i++)
	{
		if ((enemyWave.at(i)->locationX == 7 && enemyWave.at(i)->locationY == 6) || !enemyWave.at(i)->alive)
		{
			enemyWave.erase(enemyWave.begin() + i);
		}
		else enemyWave.at(i)->Update();
	}

	if (enemyWave.size() == 0 && tempEnemyWave.size() == 0) {
		waveEnd = true;
	}

	if (waveNum == waveMax) {
		gameOver = true;
		//cout << "Game Over!" << endl;
	}
}