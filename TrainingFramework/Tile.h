#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include "Object.h"
#include <iostream>
class Tile:public Object
{
public:
	Vector2 tileNum;
	Vertex tileVertices[4];
	int tileType;
	bool canBuild = true;
	GLuint vboId;
	GLuint iboId;

	//Matrix MVP;
	Shaders* myShaders;
	Texture tileTexture;

	Tile();
	Tile(int type, int numX, int numY, float x, float y, Shaders* shader);
	Tile(int type, int numX, int numY);
	

	void Bind();
	void Draw();
};
