#include "stdafx.h"
#include "Tile.h"
#include "Shaders.h"
#include "Vertex.h"
#include <iostream>

Tile::Tile()
{

}

Tile::Tile(int type, int numX, int numY, float x, float y, Shaders shaders)
{
	tileType = type;
	if (tileType == 0) { 
		canBuild = true; 
		tileTexture = Texture("../Resources/grass_tile.tga");
	}
	else {
		canBuild = false;
		tileTexture = Texture("../Resources/sand_tile.tga");
	}
	tileNum.x = numX;
	tileNum.y = numY;
	myShaders = shaders;
	MVP.SetIdentity();

	tileVertices[0].pos.x = x;		   tileVertices[0].pos.y = y;		 tileVertices[0].pos.z = 0;
	tileVertices[1].pos.x = x + 0.15f; tileVertices[1].pos.y = y;		 tileVertices[1].pos.z = 0;
	tileVertices[2].pos.x = x + 0.15f; tileVertices[2].pos.y = y - 0.2f; tileVertices[2].pos.z = 0;
	tileVertices[3].pos.x = x;		   tileVertices[3].pos.y = y - 0.2f; tileVertices[3].pos.z = 0;

	tileVertices[0].coords.x = 0.0f;	tileVertices[0].coords.y = 0.0f;
	tileVertices[1].coords.x = 1.0f;	tileVertices[1].coords.y = 0.0f;
	tileVertices[2].coords.x = 1.0f;	tileVertices[2].coords.y = 1.0f;
	tileVertices[3].coords.x = 0.0f;	tileVertices[3].coords.y = 1.0f;

	/*std::cout << "Tile " << tileNum.x << " " << tileNum.y << " type: " << tileType << std::endl;
	for (int i = 0; i < 4; i++) {
		std::cout << tileVertices[i].pos.x << " " << tileVertices[i].pos.y << std::endl;
	}*/
}

void Tile::Bind()
{
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tileVertices), tileVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Tile::Draw()
{
	glUseProgram(myShaders.program);
	glBindTexture(GL_TEXTURE_2D, tileTexture.mTextureId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	if (myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (myShaders.uvAttribute != -1)
	{
		//glUniform1i(myShaders.uvAttribute, 0);
		glEnableVertexAttribArray(myShaders.uvAttribute);
		glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Vector3)));

	}

	GLushort indices[]{ 0,1,2 };
	GLushort in[]{ 0,2,3 };
	
	glUniformMatrix4fv(myShaders.u_MVP, 1, GL_FALSE, *MVP.m);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, &indices);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, &in);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}