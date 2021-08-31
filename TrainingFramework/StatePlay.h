#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <iostream>
#include <vector>
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
	Shaders* myShaders = new Shaders();
	PlayField pf = PlayField();
	std::vector <Tower*> towerList;
	std::vector <Object*> towerButtonList;
	vector <Object*> functionButtonList;
	vector <Frame*> frameList;

	vector <Object*> objList;
	Object* upgradeButton;
	Object* sellButton;
	Object* nextWaveButton;

	//Object* bugFixButton;
	Object* bgPlay = new Object();
	Object* background = new Object();
	Object* hpIcon = new Object();
	Object* moneyIcon = new Object();

	std::string strLives = "Lives: " + std::to_string(pf.HP);
	char const* cLives = strLives.c_str();
	Text* lives = new Text(cLives, 800, 300, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 0.0, 0.0, 1.0), 70);
	//Text* showHP = new Text("Lives :", 730, 350, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 0.0, 0.0, 1.0), 70);

	std::string strMoney = std::to_string(pf.money);
	char const* cMoney = strMoney.c_str();
	Text* money = new Text(cMoney, 800, 220, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 0.0, 1.0), 70);
	//Text* showMoney = new Text("Gold :", 730, 310, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 0.0, 1.0), 70);

	//int currentTower = -1;
	std::string strTowerDmg;
	std::string strTowerSellFor;
	std::string strTowerStats;
	
	Text* towerStat = new Text("!", 10, 10, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 0.0, 0.0, 1.0), 60);

	Text* gameOverText = new Text("GAME OVER!", 320, 370, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 0.0, 0.0, 1.0), 200);
	Text* winText = new Text("YOU WIN!", 310, 370, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 200);

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

	bool mouseOnTower = false;

	void init();
	void Draw(Shaders* textShaders);
	void Update(float deltaTime);
	bool IsBuildable(int xPos, int yPos);
	bool CheckSelectionOption(int x, int y);
	void OnMouseClick(int x, int y);
	void OnMouseOver(int x, int y);
	void CleanUp();
	
	int FindIndexOfTower(int x, int y);

	StatePlay();
};
