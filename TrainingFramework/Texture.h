#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
class Texture
{
public:
	int ID;
	char* mTgaFilePath;
	GLenum mTiling, fTilling1, fTilling2;
	void ConfigTexture();
	GLuint mTextureId;
	void Init();
	Texture();
	Texture(const char* tgaFilePath, int id = 0, GLenum tiling = GL_REPEAT, GLenum fTilling1 = GL_LINEAR, GLenum fTilling2 = GL_LINEAR);
	~Texture();
};