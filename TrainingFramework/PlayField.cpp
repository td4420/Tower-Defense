#include "stdafx.h"
#include "PlayField.h"
#include "Tile.h"
#include "Shaders.h"
#include <vector>

PlayField::PlayField()
{

}

void PlayField::Init(Shaders shaders)
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
}
