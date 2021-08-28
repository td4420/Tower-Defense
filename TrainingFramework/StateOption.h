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
	char const* vgame = tmpGame.c_str();

	int volumeNen = 50;
	std::string tmpNen = std::to_string(volumeNen);
	char const* vnen = tmpNen.c_str();

	vector<Text*> listText;
	void init();
	void Update(float deltaTime);
	void Draw(Shaders* textShader, Shaders* shapeShader);
	void OnMouseOver(int x, int y);
	void OnMouseClick(int x, int y);
	void CleanUp();
};