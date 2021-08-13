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

#define MOVE_FORWARD 1
#define MOVE_BACKWARD 1 << 1
#define MOVE_LEFT 1 << 2
#define MOVE_RIGHT 1 << 3
#define ROTATE_UP 1 << 4
#define ROTATE_DOWN 1 << 5
#define ROTATE_LEFT 1 << 6
#define ROTATE_RIGHT 1 << 7


int keyPressed = 0;
//SceneManager* scenemanager = SceneManager::GetInstance("../ResourcesPacket/SM.txt");
Shaders myShaders;
Camera* camera;

PlayField pf = PlayField();
Enemies e = Enemies(1);
Enemies f = Enemies(2);
Enemies tank = Enemies(3);

Tower t = Tower(0);
Tower gun = Tower(1);

std::vector <Enemies*> wave;
std::vector <Tower*> towerList;
std::vector <Object*> towerButtonList;
Object* upgradeButton;

int selectMenuOption = -1;
int NumMap[7][8] =
{
	1,1,0,0,0,0,0,0,
	0,1,1,0,0,0,0,0,
	0,0,1,1,1,1,1,0,
	0,0,0,0,0,0,1,0,
	0,0,0,1,1,1,1,0,
	0,0,0,1,0,0,0,0,
	0,0,0,1,1,1,1,1
};

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	pf.Init(myShaders);
	

	wave.push_back(&e);//1 buffer
	wave.push_back(&f);
	wave.push_back(&tank);
	for (int i = 0; i < wave.size(); i++) {
		wave.at(i)->o_shaders = myShaders;
		wave.at(i)->InitObject();
	}

	//t.o_shaders = myShaders;//
	//t.InitObject();
	t.Build(3, 3);

	//gun.o_shaders = myShaders;
	//gun.InitObject();
	gun.Build(5, 3);
	//gun.Upgrade();//bug af

	towerList.push_back(&t);
	towerList.push_back(&gun);
	for (int i = 0; i < towerList.size(); i++) {//fix InitObject MVP.SetIdentity, move that to build
		towerList.at(i)->o_shaders = myShaders;
		towerList.at(i)->InitObject();
	}

	//cout << t.o_Texture.size() << endl;
	t.Upgrade();
	t.Upgrade();
	t.Upgrade();
	gun.Upgrade();
	gun.Upgrade();
	

	//add Button Tower 
	Object* archerTowerButton = new Object();
	archerTowerButton->o_Model = Model("../Resources/model.nfg");
	archerTowerButton->o_Texture.push_back(Texture("../ResourcesPacket/Textures/archerTowerButton.tga"));
	archerTowerButton->Build(10*0.15f, 1*-0.2f);

	Object* mortarTowerButton = new Object();
	mortarTowerButton->o_Model = Model("../Resources/model.nfg");
	mortarTowerButton->o_Texture.push_back(Texture("../ResourcesPacket/Textures/mortarTowerButton.tga"));
	mortarTowerButton->Build(10 * 0.15f, 3 * -0.2f);

	towerButtonList.push_back(archerTowerButton);
	towerButtonList.push_back(mortarTowerButton);

	for (int i = 0; i < towerButtonList.size(); i++) {
		towerButtonList.at(i)->o_shaders = myShaders;
		towerButtonList.at(i)->InitObject();
	}

	// init upgrade button
	upgradeButton = new Object();
	upgradeButton->o_Model = Model("../Resources/model.nfg");
	upgradeButton->o_Texture.push_back(Texture("../ResourcesPacket/Textures/upgrade_button.tga"));
	upgradeButton->o_shaders = myShaders;
	upgradeButton->Build(12 * 0.15f, 1 * -0.2f);
	upgradeButton->InitObject();

	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	
}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glUseProgram(myShaders.program);

	pf.Draw();
	
	if (wave.size() != 0) {
		for (int i = 0; i < wave.size(); i++) {
			wave.at(i)->DrawObject();
		}
	}
	
	/*t.DrawObject();
	gun.DrawObject();
	t.Shoot();
	gun.Shoot();*/

	for (int i = 0; i < towerList.size(); i++) {
		towerList.at(i)->DrawObject();
		towerList.at(i)->Shoot();
	}

	for (int i = 0; i < towerButtonList.size(); i++) {
		towerButtonList.at(i)->DrawObject();
	}
	
	//draw upGrage Button
	upgradeButton->DrawObject();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	if (keyPressed & MOVE_FORWARD) {
		camera->MoveForward(deltaTime);
	}

	if (keyPressed & MOVE_BACKWARD) {
		camera->MoveBackward(deltaTime);
	}

	if (keyPressed & MOVE_LEFT) {
		camera->MoveToLeft(0.01f);
	}

	if (keyPressed & MOVE_RIGHT) {
		camera->MoveToRight(0.01f);
	}
	if (keyPressed & ROTATE_UP) {
		camera->RotationUp(deltaTime);
	}

	if (keyPressed & ROTATE_DOWN) {
		camera->RotationDown(deltaTime);
	}
	if (keyPressed & ROTATE_LEFT) {
		camera->RotationLeft(0.01f);
	}
	if (keyPressed & ROTATE_RIGHT) {
		camera->RotationRight(0.01f);
	}
	//scenemanager->Update(deltaTime);
	for (int i = 0; i < wave.size(); i++) {
		if (wave.at(i)->alive) wave.at(i)->Update();
		else
		{
			wave.erase(wave.begin() + i);
		}
	}
	
	//t.AddEnemiesInRange(wave);//2 buffers
	//t.RemoveEnemiesOutOfRange();

	//gun.AddEnemiesInRange(wave);//2 buffers
	//gun.RemoveEnemiesOutOfRange();

	////cout << t.projectileOnScreen.size() << endl;
	//if (t.projectileOnScreen.size() != 0) {
	//	for (int i = 0; i < t.projectileOnScreen.size(); i++) {
	//		t.projectileOnScreen.at(i)->Move(t.projectileOnScreen.at(i)->GetAngleToEnemies());
	//	}
	//}

	//if (gun.projectileOnScreen.size() != 0) {
	//	for (int i = 0; i < gun.projectileOnScreen.size(); i++) {
	//		gun.projectileOnScreen.at(i)->Move(gun.projectileOnScreen.at(i)->GetAngleToEnemies());
	//	}
	//}

	for (int i = 0; i < towerList.size(); i++) {
		towerList.at(i)->AddEnemiesInRange(wave);
		towerList.at(i)->RemoveEnemiesOutOfRange();

		if (towerList.at(i)->projectileOnScreen.size() != 0) {
			for (int j = 0; j < towerList.at(i)->projectileOnScreen.size(); j++) {
				towerList.at(i)->projectileOnScreen.at(j)->Move(towerList.at(i)->projectileOnScreen.at(j)->GetAngleToEnemies());
			}
		}
	}

	//cout << wave.at(0)->currentHP << endl;
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		if (key == VK_UP)
		{
			keyPressed = keyPressed | ROTATE_UP;
			return;
		}

		if (key == VK_DOWN)
		{
			keyPressed = keyPressed | ROTATE_DOWN;
			return;
		}

		if (key == VK_LEFT)
		{
			keyPressed = keyPressed | ROTATE_LEFT;
			return;
		}
		if (key == VK_RIGHT)
		{
			keyPressed = keyPressed | ROTATE_RIGHT;
			return;
		}
		if (key == 'A')
		{
			keyPressed = keyPressed | MOVE_LEFT;
			return;
		}
		if (key == 'D')
		{
			keyPressed = keyPressed | MOVE_RIGHT;
			return;
		}
		if (key == 'W')
		{
			keyPressed = keyPressed | MOVE_FORWARD;
			return;
		}
		if (key == 'S')
		{
			keyPressed = keyPressed | MOVE_BACKWARD;
			return;
		}
	}
	else
	{
		if (key == VK_UP)
		{
			keyPressed = keyPressed ^ ROTATE_UP;
			return;
		}

		if (key == VK_DOWN)
		{
			keyPressed = keyPressed ^ ROTATE_DOWN;
			return;
		}

		if (key == VK_LEFT)
		{
			keyPressed = keyPressed ^ ROTATE_LEFT;
			return;
		}
		if (key == VK_RIGHT)
		{
			keyPressed = keyPressed ^ ROTATE_RIGHT;
			return;
		}
		if (key == 'A')
		{
			keyPressed = keyPressed ^ MOVE_LEFT;
			return;
		}
		if (key == 'D')
		{
			keyPressed = keyPressed ^ MOVE_RIGHT;
			return;
		}
		if (key == 'W')
		{
			keyPressed = keyPressed ^ MOVE_FORWARD;
			return;
		}
		if (key == 'S') {
			keyPressed = keyPressed ^ MOVE_BACKWARD;
			return;
		}
	}
}

bool CheckSelectionOption(int x, int y) {
	for (int i = 0; i < towerButtonList.size(); i++) {
		float x_tower = towerButtonList.at(i)->o_position.x / 0.15f * 70;
		float y_tower = towerButtonList.at(i)->o_position.y / -0.2f * 70;
		if (x_tower <= x && x <= x_tower + 70 && y_tower <= y && y <= y_tower + 70) {
			selectMenuOption = i;
			printf("\ntower selection is: %d", i);
			return true;
		}
	}
	float x_upgrade_button = upgradeButton->o_position.x / 0.15f * 70;
	float y_upgrade_button = upgradeButton->o_position.y / -0.2f * 70;
	if (x_upgrade_button <= x && x <= x_upgrade_button + 70
		&& y_upgrade_button <= y && y <= y_upgrade_button + 70) {
		selectMenuOption = towerButtonList.size();
		printf("\nupgrade button is selected ");
		return true;
	}
	return false;
}
void TouchActionDown(ESContext* esContext, int x, int y)
{
}

bool IsBuildable(int xPos, int yPos) {
	for (int i = 0; i < towerList.size(); i++) {
		Vector3 o_position = towerList.at(i)->o_position;
		if (xPos * 0.15f == o_position.x && yPos * -0.2f == o_position.y) {
			printf("\n has avaiable tower in here");
			return false;
		}
	}
	return true;
}

void TouchActionUp(ESContext* esContext, int x, int y)
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
					printf("\ntower at: %d, %d upgrade", xPos, yPos);
					towerList.at(i)->Upgrade();
					selectMenuOption = -1;
					break;
				}
			}
			if (!CheckSelectionOption(x, y)) selectMenuOption = -1;

		}
	}
}
void TouchActionDrag(ESContext* esCotext, int x, int y) {
	//move drag
}
void TouchActionMove(ESContext* esContext, int x, int y)
{
	
}
void CleanUp()
{
	for (int i = 0; i < t.projectileOnScreen.size(); i++) {
		//t.projectileOnScreen.at(i)->~Projectile();
		delete t.projectileOnScreen.at(i);
	}

	/*for (int i = 0; i < wave.size(); i++) {
		wave.at(i)->~Enemies();
		delete wave.at(i);
	}*/
	/*for (int i = 0; i < towerList.size(); i++) {//null pointer deletion?
		delete towerList.at(i);
	}*/
	
	/*for (int i = 0; i < scenemanager->numberOfObject; i++)
	{
		scenemanager->s_ListObject.at(i)->~Object();
	}*/
	//delete t.enemiesInRange.at(0);//bad pointer deletion
}

int _tmain(int argc, TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Giant TD", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;


	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);
	esRegisterMouseDragFunc(&esContext, TouchActionDrag);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}