#pragma once
#include"StateBase.h"
#include"Model.h"
#include"Texture.h"
#include"Vertex.h"
#include"Text.h"
#include<sstream>
#include<iostream>
class StateWelcome : public StateBase {
public:
	StateControl state = StateControl::StateWelcome;
	Model* modelLogo;
	Texture* textureLogo;
	
	char* fileState = "../ResourcesPacket/StateWelcome.txt";
	int percentLoad = 0;

	std::string tmp = std::to_string(percentLoad);
	char const* num_char = tmp.c_str();

	Text* loading = new Text(num_char ,410,320, "../Font/OlympusMount.ttf", 1,1, Vector4(0.6,0.6,0.6,0.6), 48);
	
	void init();
	void Update(float deltaTime);
	void DrawLogo(Shaders s);
	void Draw(Shaders ss);
};