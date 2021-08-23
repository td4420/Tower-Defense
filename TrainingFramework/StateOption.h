#pragma once
#include"StateBase.h"
#include"Text.h"
#include"Globals.h"
#include<vector>
using namespace std;
class StateOption : public StateBase {
public:
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
	void OnMouseClick(int x, int y);
};