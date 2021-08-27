#pragma once
#include"StateBase.h"
#include"Text.h"
#include"Model.h"
#include"Texture.h"
#include"Globals.h"
#include"Vertex.h"
#include<vector>
class StateHelp: public StateBase {
public:
	Model* model;
	Texture* texture;
	Text* back;
	Matrix pos, scale, mvp;

	void init();
	void Update(float deltaTime);
	void Draw(Shaders* textShader, Shaders* shapeShader);
	void OnMouseOver(int x, int y);
	void OnMouseClick(int x, int y);
	void CleanUp();
};