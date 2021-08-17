#pragma once
#include"StateBase.h"
#include"Model.h"
#include"Texture.h"
#include"Vertex.h"
#include"Text.h"
#include"Object.h"
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

	Text* loading = new Text(num_char ,350,320, "../Font/OceanSummer.ttf", 1,1, Vector4(0.6,0.6,0.6,0.6), 68);
	Text* tapToStart = new Text("TAP TO START!", 340, 320, "../Font/OceanSummer.ttf", 1, 1, Vector4(0.6, 0.6, 0.6, 0.6), 68);
	void init();
	void Update(float deltaTime);
	void OnMouseOver(int x, int y);
	void OnMouseClick(int x, int y);
	void Draw(Shaders textShader, Shaders shapeShader);
};