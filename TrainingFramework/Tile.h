#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include <iostream>
class Tile
{
public:
	Vector2 tileNum;
	Vertex tileVertices[4];
	int tileType;
	bool canBuild = true;
	GLuint vboId;
	GLuint iboId; 

	Matrix MVP;
	Shaders myShaders;
	Texture tileTexture = Texture("../Resources/grass_tile.tga");

	Tile();
	Tile(int type, int numX, int numY, float x, float y, Shaders shader);

	void Bind();
	void Draw();
};

