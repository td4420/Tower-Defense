#pragma once
#pragma once
#include "../Utilities/utilities.h"
#include "ft2build.h"
#include "Shaders.h"
#include <cstdio>
#include FT_FREETYPE_H
class Text {
public:
	Vector4 color = Vector4(1.0, 0.5, 1.0, 1.0);
	float scaleX, scaleY;
	float posX, posY;
	float widthText, heightText;
	char const* text;
	char* fileFont;
	int size;
	bool isChoose = false;
	FT_Library m_ft;
	FT_Face m_face;
	FT_GlyphSlot m_glyphSlot;
	GLuint textVBO;
	GLuint textImgTexture;
	void init();
	void RenderText(Shaders* shader);
	bool checkChoose(int x, int y);
	Text(const char* s, float x, float y, const char* fileFont, float scaleX, float scaleY, Vector4 color, int size);
	Text(const char* s, const char* fileFont, float scaleX, float scaleY, Vector4 color, int size, float x, float y);
	~Text();
};