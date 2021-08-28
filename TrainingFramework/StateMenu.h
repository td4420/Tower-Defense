#pragma once
#include"StateBase.h"
#include"Text.h"
#include<vector>
#include"Model.h"
#include"Texture.h"
#include"Shaders.h"
#include"Object.h"
using namespace std;
class StateMenu :public StateBase {
public:
	StateControl state = StateControl::StateMenu;
	Matrix posM, scaleM, mvpM;
	vector<Text*> listText;
	Text* play;
	Text* options;
	Text* helps;
	Text* quit;
	Model* modelMenu;
	Texture* textureMenu;

	void init();
	void Update(float deltaTime);
	void Draw(Shaders* textShader, Shaders* shapeShader);
	void handleEvent();
	void OnMouseOver(int x, int y);
	void OnMouseClick(int x, int y);
	void CleanUp();
	StateMenu();
	~StateMenu();
};