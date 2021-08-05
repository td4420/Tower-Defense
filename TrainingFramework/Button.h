#pragma once
#include "../Utilities/utilities.h"
#include"Model.h"
#include"Texture.h"
#include"Shaders.h"
#include<vector>
#include"Vertex.h"
#include"Text.h"
using namespace std;
class Button {
public:
	Text text;
	float posX, posY, height, width;

	void init();
	void Draw(Shaders shader, Vector4 color, float scaleX, float scaleY);



};