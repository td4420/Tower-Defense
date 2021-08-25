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
#include "Frame.h"
#include "Text.h"
#include <sstream>
class StatePlay
{
public:
	Shaders myShaders;
	//Shaders *textShaders = new Shaders();
	PlayField pf = PlayField();
	std::vector <Tower*> towerList;
	std::vector <Object*> towerButtonList;
	vector <Frame*> frameList;
	Object* upgradeButton;
	Object* sellButton;
	Object* nextWaveButton;

	Object* background;

	std::string strLives = std::to_string(pf.HP);
	char const* cLives = strLives.c_str();
	Text* lives = new Text(cLives, 810, 350, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 0.0, 0.0, 1.0), 68);

	std::string strMoney = std::to_string(pf.money);
	char const* cMoney = strMoney.c_str();
	Text* money = new Text(cMoney, 810, 310, "../Font/OceanSummer.ttf", 1, 1, Vector4(0.0, 1.0, 0.0, 1.0), 68);
	//Text* gold;

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
	void Draw(Shaders* textShaders);
	void Update();
	bool IsBuildable(int xPos, int yPos);
	bool CheckSelectionOption(int x, int y);
	void OnMouseClick(int x, int y);
	void CleanUp();


	StatePlay();
};
