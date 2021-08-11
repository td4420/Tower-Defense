#pragma once
#include"StateBase.h"
#include"Text.h"
#include<vector>
#include"Model.h"
#include"Texture.h"
#include"Shaders.h"
#include"Object.h"
using namespace std;
class StateMenu:public StateBase {
public:
	StateControl state = StateControl::StateMenu;
	vector<Text*> listText;
	Text* play;
	Text* options;
	Text* helps;
	Text* quit;
	Model* modelLogo;
	Texture* textureLogo;
	char* fileState = "../ResourcesPacket/StateMenu.txt";
	void init();
	void Update(float deltaTime);
	void Draw(Shaders s);
	void DrawLogo(Shaders ss);
	void handleEvent();
	StateMenu();
	~StateMenu();
};