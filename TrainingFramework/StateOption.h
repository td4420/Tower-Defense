#pragma once
#include"StateBase.h"
#include"Text.h"
#include"Globals.h"
#include"Model.h"
#include"Texture.h"
#include"Vertex.h"
#include<sstream>
#include<string>
#include<iostream>
#include<vector>
using namespace std;
class StateOption : public StateBase {
/*public:
	Text* back = new Text("BACK", 10 , Globals::screenHeight - 32.5, "../Font/OceanSummer.ttf", 1, 1, Vector4(0.5, 0.5, 0.5, 0.5), 48);
	Text* nhacNen = new Text("NHAC NEN :", 100, 550, "../Font/OceanSummer.ttf", 1, 1, Vector4(0.5, 0.5, 0.5, 0.5), 48);
	Text* onNhacNen = new Text("5", 550, 550, "../Font/wingdings2.ttf", 1, 1, Vector4(0.5, 0.5, 0.5, 0.5), 48);
	Text* offNhacNen = new Text("6", 550, 550, "../Font/wingdings2.ttf", 1, 1, Vector4(0.5, 0.5, 0.5, 0.5), 48);
	Text* changeNhacNen = new Text("|____________________|", 200, 550, "../Font/OceanSummer.ttf", 1, 1, Vector4(0.5, 0.5, 0.5, 0.5), 48);
	
	bool onSound;
	vector<Text*> listText;
	void init();
	void Update(float deltaTime);
	void Draw(Shaders* textShader, Shaders* shapeShader);
	void OnMouseOver(int x, int y);
	void OnMouseClick(int x, int y);*/
public:
	Text* back;

	Text* nhacNen;
	Text* onNhacNen;
	Text* offNhacNen;
	Text* changeNhacNen;
	Text* tangVolumeNen;
	Text* giamVolumeNen;

	Text* nhacGame;
	Text* onNhacGame;
	Text* offNhacGame;
	Text* changeNhacGame;
	Text* tangVolumeGame;
	Text* giamVolumeGame;

	Model* modelLogo;
	Texture* textureLogo;
	Matrix pos, scale, mvp;
	bool onSoundNen;
	bool onSoundGame;

	int volumeGame = 50;
	std::string tmpGame = std::to_string(volumeGame);

	int volumeNen = 50;
	std::string tmpNen = std::to_string(volumeNen);

	vector<Text*> listText;
	void init();
	void Update(float deltaTime);
	void Draw(Shaders* textShader, Shaders* shapeShader);
	void OnMouseOver(int x, int y);
	void OnMouseClick(int x, int y);
	void CleanUp();
};