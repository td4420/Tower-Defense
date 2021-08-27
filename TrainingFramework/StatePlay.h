#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <iostream>
#include <vector>
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Tile.h"
#include "PlayField.h"
#include "Enemies.h"
#include "Tower.h"
#include"Text.h"
class StatePlay
{
public:
	Shaders myShaders;
	PlayField pf = PlayField();
	std::vector <Tower*> towerList;
	std::vector <Object*> towerButtonList;
	Object* upgradeButton;
	Object* sellButton;

	Text* lives = new Text("TEST", "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 45, -1, -0.8);

	Model* modelLogo;
	Texture* textureLogo;
	Matrix posP, scaleP, mvpP;

	int selectMenuOption = -1;
	int NumMap[7][8] =
	{
		1,1,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,1,0,
		0,1,1,1,1,1,1,0,
		0,1,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1
	};

	void init();
	void Draw(Shaders* textShader, Shaders* shapeShader);
	void Update();
	bool IsBuildable(int xPos, int yPos);
	bool CheckSelectionOption(int x, int y);
	void OnMouseClick(int x, int y);
	void CleanUp();


	StatePlay();
};
