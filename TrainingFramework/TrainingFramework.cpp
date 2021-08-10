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
Enemies e = Enemies(myShaders, 60, 0.002f, 3);
Tower t = Tower();
//Projectile bullet = Projectile(0, t.towerPos.x, t.towerPos.y);
std::vector <Enemies*> wave;

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	pf.Init(myShaders);

	e.o_shaders = myShaders;//must have
	e.InitObject();

	wave.push_back(&e);//1 buffer
	t.o_shaders = myShaders;//must have
	t.InitObject();
	t.Build(5, 3);
	
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	
}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glUseProgram(myShaders.program);
	//cout << t.enemiesInRange.at(0)->locationX << " " << t.enemiesInRange.at(0)->locationY << endl;
	//cout << t.towerPos.x << " " << t.towerPos.y << endl;

	pf.Draw();
	e.DrawObject();
	
	t.DrawObject();
	
	//scenemanager->Draw();
	t.Shoot();
	/*if (!t.projectileOnScreen.size() != 0) {
		for (int i = 0; i < t.projectileOnScreen.size(); i++) {
			t.projectileOnScreen.at(i)->InitObject();
			t.projectileOnScreen.at(i)->DrawObject();
		}
	}*/
	
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
	e.Update();

	t.AddEnemiesInRange(wave);//2 buffers
	t.RemoveEnemiesOutOfRange();

	//cout << t.projectileOnScreen.size() << endl;
	if (t.projectileOnScreen.size() != 0) {
		//cout << t.projectileOnScreen.size();
		for (int i = 0; i < t.projectileOnScreen.size(); i++) {
			t.projectileOnScreen.at(i)->Move(t.projectileOnScreen.at(i)->GetAngleToEnemies());
		}
	}
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

void CleanUp()
{
	for (int i = 0; i < t.projectileOnScreen.size(); i++) {
		//t.projectileOnScreen.at(i)->~Projectile();
		delete t.projectileOnScreen.at(i);
	}
	
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

	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}