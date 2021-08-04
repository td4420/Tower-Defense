#pragma once
#include <vector>
#include "Tile.h"
#include "Shaders.h"
class PlayField
{
public:
	const float disX = 0.15f;
	const float disY = 0.2f;

	Tile TileMap[7][8];
	//std::vector <int*> NumMap;
	const int mapHeight = 7;
	const int mapWidth = 8;

	void Init(Shaders myShaders);
	void Draw();

	PlayField();
	//~PlayField();
};

