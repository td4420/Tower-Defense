#pragma once
#include"Object.h"
#include"StateBase.h"
#include"Model.h"
#include"Texture.h"
#include"Vertex.h"
class StateLogo : public StateBase {
public:
	Model* modelLogo;
	Texture* textureLogo;

	Matrix scale, trans, mvp;
	int time = 30;
	void init();
	void Update(float deltaTime);
	void Draw(Shaders textShader, Shaders shapeShader);
};