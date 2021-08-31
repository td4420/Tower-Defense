
#pragma once
#include"StateBase.h"
#include"Text.h"
#include"Model.h"
#include"Texture.h"
#include"Globals.h"
#include"Vertex.h"
#include"Object.h"
#include<vector>
class StateMap : public StateBase {
public:
	Object* bg;
	Text* back;
	int Map;
	Object* map1;
	Object* map2;
	Text* M1;
	Text* M2;
	Shaders* myShader = new Shaders();
	void init();
	void Update(float deltaTime);
	void Draw(Shaders* textShader, Shaders* shapeShader);
	void OnMouseOver(int x, int y);
	void OnMouseClick(int x, int y);
	void CleanUp();
};