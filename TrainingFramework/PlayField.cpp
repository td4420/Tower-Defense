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
	for (int i = 0; i < enemyWave.size(); i++) {
		delete enemyWave.at(i);
	}

	for (int i = 0; i < tempEnemyWave.size(); i++) {
		delete tempEnemyWave.at(i);
	}
}

void PlayField::Init(Shaders shaders)
{
	myShaders = shaders;
	int NumMap[7][8];
	/*{
		1,1,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,1,0,
		0,0,0,1,1,1,1,0,
		0,0,0,1,0,0,0,0,
		0,0,0,1,1,1,1,1
	};*/

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
}

void PlayField::Draw()
{
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			TileMap[i][j].Draw();
		}
	}

	InitEnemyWave();

	SpawnEnemy();

	for (int i = 0; i < enemyWave.size(); i++) {
		enemyWave.at(i)->DrawObject();
	}
}

void PlayField::InitEnemyWave()
{
	if (waveEnd) {
		waveEnd = false;
		for (int j = 0; j < waveLength; j++) 
		{
			//cout << "[" << waveNum << "][" << j << "] ";
			if (enemyWaveEasy[waveNum][j] != 0) {
				Enemies* e = new Enemies(enemyWaveEasy[waveNum][j]);
				e->o_shaders = myShaders;
				e->InitObject();
				tempEnemyWave.push_back(e);
			}
		}
		if (waveNum<4) waveNum += 1;
	}
}

void PlayField::SpawnEnemy() {
	//cout << tempEnemyWave.size() << " ";
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
		if (enemyWave.at(i)->alive) enemyWave.at(i)->Update();
		else {
			delete enemyWave.at(i);
			enemyWave.erase(enemyWave.begin() + i);
		}
	}

	if (enemyWave.size() == 0 && tempEnemyWave.size()==0) {
		waveEnd = true;
	}
	//if (enemyWave.size() == 0) waveEnd = true;
}