#pragma once
#pragma once
#include "../Utilities/utilities.h"
#include "ft2build.h"
#include "Shaders.h"
#include FT_FREETYPE_H
class Text {
public:
	float posX, posY;
	float widthText, heightText;
	char* text;
	FT_Library m_ft;
	FT_Face m_face;
	FT_GlyphSlot m_glyphSlot;
	GLuint textVBO;
	GLuint textImgTexture;
	GLuint textVAO;
	void init(char* fileFont);
	void RenderText(Shaders shader, Vector4 color, float scaleX, float scaleY);
	Text(char* s, float x, float y);
	~Text();
};