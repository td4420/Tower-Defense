#include "stdafx.h"
#include "Texture.h"
#include <iostream>
void Texture::ConfigTexture()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTiling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTiling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, fTilling1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, fTilling2);
	glGenerateMipmap(GL_TEXTURE_2D);
}
void Texture::Init()
{
	int iWidth = 0;
	int iHeight = 0;
	int iBpp = 0;
	const char* imageData = LoadTGA(mTgaFilePath, &iWidth, &iHeight, &iBpp);

	GLenum format = (iBpp == 24 ? GL_RGB : GL_RGBA);

	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);

	glTexImage2D(GL_TEXTURE_2D, 0, format, iWidth, iHeight, 0, format, GL_UNSIGNED_BYTE, imageData);
	if (imageData)
	{
		//std::cout << "Load texture succes" << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, format, iWidth, iHeight, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Fail to load texture" << std::endl;
	}
	ConfigTexture();
	glBindTexture(GL_TEXTURE_2D, 0);
	delete imageData;
}
Texture::Texture(const char* tgaFilePath, int id, GLint tiling, GLint fTilling1, GLint fTilling2)
{
	mTgaFilePath = strdup(tgaFilePath);
	this->mTiling = tiling;
	this->fTilling1 = fTilling1;
	this->fTilling2 = fTilling2;
	ID = id;
}
Texture::Texture() {

}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &mTextureId);
}