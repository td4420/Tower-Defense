#include"stdafx.h"
#include"Button.h"
#include"Model.h"
#include"Texture.h"
#include<iostream>
void Button::init() {
	posX = text.posX;
	posY = text.posY;
	height = text.heightText;
	width = text.widthText;
}
void Button::Draw(Shaders shader, Vector4 color, float scaleX, float scaleY) {
	text.RenderText(shader, color, scaleX, scaleY);
}