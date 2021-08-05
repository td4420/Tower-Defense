#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
class Texture
{
public:
	int ID;
	char* mTgaFilePath;
	GLint mTiling, fTilling1, fTilling2;
	void ConfigTexture();
	GLuint mTextureId;
	void Init();
	Texture(const char* tgaFilePath, int id, GLint tiling = GL_REPEAT, GLint fTilling1 = GL_LINEAR, GLint fTilling2 = GL_LINEAR);
	Texture();
	~Texture();
};