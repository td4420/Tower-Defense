#include "stdafx.h"
#include "Model.h"
#include "Vertex.h"
#include <string.h>
#include <conio.h>
#include <iostream>

void Model::Init()
{
	FILE* file = fopen(mModelFile, "r");
	
	int numberOfVertices;
	fscanf(file, "NrVertices: %d\n", &numberOfVertices);
	//std::cout << numberOfVertices << std::endl;
	if (numberOfVertices <= 0) return;
	Vertex *vertices = new Vertex[numberOfVertices];
	for (int i = 0; i < numberOfVertices; ++i)
	{
		float posX, posY, posZ;
		float normX, normY, normZ;
		float binormX, binormY, binormZ;
		float tgtX, tgtY, tgtZ;
		float uvX, uvY;

		int id;
		fscanf(file, "%d. ", &id);
		fscanf(file, "pos:[%f, %f, %f]; ", &posX, &posY, &posZ);
		fscanf(file, "norm:[%f, %f, %f]; ", &normX, &normY, &normZ);
		fscanf(file, "binorm:[%f, %f, %f]; ", &binormX, &binormY, &binormZ);
		fscanf(file, "tgt:[%f, %f, %f]; ", &tgtX, &tgtY, &tgtZ);
		fscanf(file, "uv:[%f, %f];\n ", &uvX, &uvY);

		(vertices + i)->pos.x = posX; (vertices + i)->pos.y = posY; (vertices + i)->pos.z = posZ;
		(vertices + i)->coords.x = uvX; (vertices + i)->coords.y = uvY;

		std::cout << "x: " << (vertices + i)->pos.x << " y: " << (vertices + i)->pos.y << " z: " << (vertices + i)->pos.z << std::endl;
		std::cout << "uvX: " << uvX << " uvY: " << uvY << std::endl;
	}
	glGenBuffers(1, &this->mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numberOfVertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	int numberOfIndices;
	fscanf(file, "NrIndices: %d\n", &numberOfIndices);
	//std::cout << numberOfIndices << std::endl;
	if (numberOfIndices <= 0)
	{
		glDeleteBuffers(1, &mVBO);
		return ;
	}
	int* indices = new int[numberOfIndices];
	for (int i = 0; i < numberOfIndices; i += 3)
	{
		int id;
		int iX, iY, iZ;
		fscanf(file, "%d. ", &id);
		fscanf(file, " %d, %d, %d\n", &iX, &iY, &iZ);
		*(indices + i) = iX; *(indices + i + 1) = iY; *(indices + i + 2) = iZ;
	}
	glGenBuffers(1, &this->mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * numberOfIndices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->mNumberOfIndices = numberOfIndices;
	delete[] indices;
	delete[] vertices;
}
Model::Model(char* modelFile,int modelID)
{
	strcpy(mModelFile,modelFile);
	ID = modelID;
}
Model::Model()
{

}
Model::~Model()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mIBO);
}