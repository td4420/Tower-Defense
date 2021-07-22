#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>

class Model
{
public:
	int ID;
	char mModelFile[50];
	GLuint mVBO;
	GLuint mIBO;
	int mNumberOfIndices;
	void Init();
	Model(char* modelFile,int modelID = 0);
	Model();
	~Model();
};