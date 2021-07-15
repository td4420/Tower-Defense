#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>

class Model
{
public:
	char* mModelFile;
	bool InitNFG(FILE* file);
	GLuint mVBO;
	GLuint mIBO;
	int mNumberOfIndices;
	void Init();
	Model(const char* modelFile);
	~Model();
};