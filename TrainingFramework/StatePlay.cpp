#include "stdafx.h"
#include "StatePlay.h"

StatePlay::StatePlay()
{

}

void StatePlay::init()
{
	
	
	myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	pf.Init(myShaders);

	for (int i = 0; i < towerList.size(); i++) {
		towerList.at(i)->o_shaders = myShaders;
		towerList.at(i)->InitObject();
	}


	//add Button Tower 
	Object* archerTowerButton = new Object();
	archerTowerButton->o_Model = Model("../Resources/model.nfg");
	archerTowerButton->o_Texture.push_back(Texture("../ResourcesPacket/Textures/archerTowerButton.tga"));
	archerTowerButton->Build(10 * 0.15f, 1 * -0.2f);

	Object* mortarTowerButton = new Object();
	mortarTowerButton->o_Model = Model("../Resources/model.nfg");
	mortarTowerButton->o_Texture.push_back(Texture("../ResourcesPacket/Textures/mortarTowerButton.tga"));
	mortarTowerButton->Build(10 * 0.15f, 3 * -0.2f);

	Object* slowTowerButton = new Object();
	slowTowerButton->o_Model = Model("../Resources/model.nfg");
	slowTowerButton->o_Texture.push_back(Texture("../ResourcesPacket/Textures/slowTowerButton.tga"));
	slowTowerButton->Build(10 * 0.15f, 5 * -0.2f);

	Object* witchTowerButton = new Object();
	witchTowerButton->o_Model = Model("../Resources/model.nfg");
	witchTowerButton->o_Texture.push_back(Texture("../ResourcesPacket/Textures/witchTowerButton.tga"));
	witchTowerButton->Build(10 * 0.15f, 7 * -0.2f);

	towerButtonList.push_back(archerTowerButton);
	towerButtonList.push_back(mortarTowerButton);
	towerButtonList.push_back(slowTowerButton);
	towerButtonList.push_back(witchTowerButton);

	for (int i = 0; i < towerButtonList.size(); i++) {
		towerButtonList.at(i)->o_shaders = myShaders;
		towerButtonList.at(i)->InitObject();
	}

	// init upgrade button
	upgradeButton = new Object();
	upgradeButton->o_Model = Model("../Resources/model.nfg");
	upgradeButton->o_Texture.push_back(Texture("../ResourcesPacket/Textures/UpgradeButton.tga"));
	upgradeButton->Build(12 * 0.15f, 0 * -0.2f);
	upgradeButton->o_shaders = myShaders;
	upgradeButton->InitObject();

	// init sell button
	sellButton = new Object();
	sellButton->o_Model = Model("../Resources/model.nfg");
	sellButton->o_Texture.push_back(Texture("../ResourcesPacket/Textures/SellButton.tga"));
	sellButton->Build(11 * 0.15f, 0 * -0.2f);
	
	sellButton->o_shaders = myShaders;
	sellButton->InitObject();

	// init sell button
	nextWaveButton = new Object();
	nextWaveButton->o_Model = Model("../Resources/model.nfg");
	nextWaveButton->o_Texture.push_back(Texture("../ResourcesPacket/Textures/NextWaveButton.tga"));
	nextWaveButton->Build(8 * 0.15f, 0 * -0.2f);
	nextWaveButton->o_shaders = myShaders;
	nextWaveButton->InitObject();
}

void StatePlay::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	pf.Draw();
	for (int i = 0; i < towerList.size(); i++) {
		towerList.at(i)->DrawObject();
		towerList.at(i)->Shoot();
	}

	for (int i = 0; i < towerButtonList.size(); i++) {
		towerButtonList.at(i)->DrawObject();
	}

	upgradeButton->DrawObject();
	sellButton->DrawObject();

	if (pf.waveEnd) {
		nextWaveButton->DrawObject();

	}


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

void StatePlay::Update()
{
	pf.Update();

	for (int i = 0; i < towerList.size(); i++) {
		towerList.at(i)->AddEnemiesInRange(pf.enemyWave);
		towerList.at(i)->RemoveEnemiesOutOfRange();

		if (towerList.at(i)->projectileOnScreen.size() != 0) {
			for (int j = 0; j < towerList.at(i)->projectileOnScreen.size(); j++) {
				if (towerList.at(i)->projectileOnScreen.at(j)->nullified == false) {
					towerList.at(i)->projectileOnScreen.at(j)->Move(towerList.at(i)->projectileOnScreen.at(j)->GetAngleToEnemies());
				}

				if (towerList.at(i)->projectileOnScreen.at(j)->nullified == true) {
					delete towerList.at(i)->projectileOnScreen.at(j);
					towerList.at(i)->projectileOnScreen.erase(towerList.at(i)->projectileOnScreen.begin() + j);
				}
			}
		}
	}
}

bool StatePlay::CheckSelectionOption(int x, int y)
{
	for (int i = 0; i < towerButtonList.size(); i++) {
		float x_tower = towerButtonList.at(i)->o_position.x / 0.15f * 70;
		float y_tower = towerButtonList.at(i)->o_position.y / -0.2f * 70;
		if (x_tower <= x && x <= x_tower + 70 && y_tower <= y && y <= y_tower + 70) {
			selectMenuOption = i;
			//printf("\ntower selection is: %d", i);
			return true;
		}
	}
	float x_upgrade_button = upgradeButton->o_position.x / 0.15f * 70;
	float y_upgrade_button = upgradeButton->o_position.y / -0.2f * 70;
	if (x_upgrade_button <= x && x <= x_upgrade_button + 70
		&& y_upgrade_button <= y && y <= y_upgrade_button + 70) {
		selectMenuOption = towerButtonList.size();
		//printf("\nupgrade button is selected ");
		return true;
	}

	float x_sell_button = sellButton->o_position.x / 0.15f * 70;
	float y_sell_button = sellButton->o_position.y / -0.2f * 70;
	if (x_sell_button <= x && x <= x_sell_button + 70
		&& y_sell_button <= y && y <= y_sell_button + 70) {
		selectMenuOption = towerButtonList.size() + 1;
		return true;
	}

	float x_wave_button = nextWaveButton->o_position.x / 0.15f * 70;
	float y_wave_button = nextWaveButton->o_position.y / -0.2f * 70;
	if (x_wave_button <= x && x <= x_wave_button + 70
		&& y_wave_button <= y && y <= y_wave_button + 70) {
		selectMenuOption = towerButtonList.size() + 2;
		return true;
	}
	return false;
}

bool StatePlay::IsBuildable(int xPos, int yPos)
{
	for (int i = 0; i < towerList.size(); i++) {
		Vector3 o_position = towerList.at(i)->o_position;
		if (xPos * 0.15f == o_position.x && yPos * -0.2f == o_position.y) {
			//printf("\n has avaiable tower in here");
			return false;
		}
	}
	return true;
}

void StatePlay::OnMouseClick(int x, int y)
{
	if (selectMenuOption == -1) {
		CheckSelectionOption(x, y);
	}

	//upgrade or build tower
	if (selectMenuOption != -1) {
		//build Tower
		if (selectMenuOption > -1 && selectMenuOption < towerButtonList.size()) {
			int xPos = static_cast<int>(std::round(x / 70));
			int yPos = static_cast<int>(std::round(y / 70));
			if (-1 < xPos && xPos < 8 && -1 < yPos && yPos < 7) {
				if (NumMap[yPos][xPos] == 0 && IsBuildable(xPos, yPos)) {
					Tower* t = new Tower(selectMenuOption);//super leak :V

					Shaders s = Shaders();
					s.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
					t->o_shaders = s;
					t->Build(xPos, yPos);
					t->InitObject();
					towerList.push_back(t);
				}
				selectMenuOption = -1;
			}
			else if (!CheckSelectionOption(x, y)) selectMenuOption = -1;

		}
		else if (selectMenuOption == towerButtonList.size()) {
			//upgrade Button
			int xPos = static_cast<int>(std::round(x / 70));
			int yPos = static_cast<int>(std::round(y / 70));

			//get tower upgrade
			for (int i = 0; i < towerList.size(); i++) {
				Vector3 o_positon = towerList.at(i)->o_position;
				if (xPos * 0.15f == o_positon.x && yPos * -0.2f == o_positon.y) {
					//printf("\ntower at: %d, %d upgrade", xPos, yPos);
					towerList.at(i)->Upgrade();
					selectMenuOption = -1;
					break;
				}
			}
			if (!CheckSelectionOption(x, y)) selectMenuOption = -1;

		}
		//sell Button
		else if (selectMenuOption == towerButtonList.size() + 1) {
			int xPos = static_cast<int>(std::round(x / 70));
			int yPos = static_cast<int>(std::round(y / 70));
			//get tower upgrade
			for (int i = 0; i < towerList.size(); i++) {
				Vector3 o_positon = towerList.at(i)->o_position;
				if (xPos * 0.15f == o_positon.x && yPos * -0.2f == o_positon.y) {
					delete towerList.at(i);
					towerList.erase(towerList.begin() + i);
					selectMenuOption = -1;
					break;
				}
			}
			if (!CheckSelectionOption(x, y)) selectMenuOption = -1;
		}
		else if (selectMenuOption == towerButtonList.size() + 2) {
			
			if (pf.waveEnd) {
				pf.nextWave = true;
				printf("\n next wave btn");
			}
			
			if (!CheckSelectionOption(x, y)) selectMenuOption = -1;
		}
	}
}

void StatePlay::CleanUp()
{
	for (int i = 0; i < towerList.size(); i++) {
		delete towerList.at(i);// bad pointer deletion if u set tower thats not pointer
	}

	for (int i = 0; i < towerButtonList.size(); i++) {
		delete towerButtonList.at(i);
	}
	delete upgradeButton;
	delete sellButton;

	for (int i = 0; i < towerList.size(); i++) {
		for (int j = 0; j < towerList.at(i)->projectileOnScreen.size(); j++) {
			delete towerList.at(i)->projectileOnScreen.at(j);
			towerList.at(i)->projectileOnScreen.clear();
		}
	}
	pf.CleanUp();
}