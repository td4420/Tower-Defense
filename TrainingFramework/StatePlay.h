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
class StatePlay
{
public:
	Shaders myShaders;
	PlayField pf = PlayField();
	std::vector <Tower*> towerList;
	std::vector <Object*> towerButtonList;
	vector <Frame*> frameList;
	Object* upgradeButton;
	Object* sellButton;

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
	void Draw();
	void Update();
	bool IsBuildable(int xPos, int yPos);
	bool CheckSelectionOption(int x, int y);
	void OnMouseClick(int x, int y);
	void CleanUp();


	StatePlay();
};
