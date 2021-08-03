#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <iostream>
#include "SceneManager.h"
#include "ResourceManager.h"
#define MOVE_FORWARD 1
#define MOVE_BACKWARD 1 << 1
#define MOVE_LEFT 1 << 2
#define MOVE_RIGHT 1 << 3
#define MOVE_UP 1 << 4
#define MOVE_DOWN 1 << 5


int keyPressed = 0;
SceneManager* scenemanager = SceneManager::GetInstance("../ResourcesPacket/SM.txt");
Shaders myShaders;
Camera* camera;
int Init(ESContext* esContext)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	scenemanager->Init();
	camera = scenemanager->camera;
	//creation of shaders and program 
	myShaders = scenemanager->s_ListObject.at(0)->o_shaders;
	return myShaders.Init(myShaders.fileVS,myShaders.fileFS);
}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scenemanager->Draw();
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
		camera->MoveToLeft(deltaTime);
	}

	if (keyPressed & MOVE_RIGHT) {
		camera->MoveToRight(deltaTime);
	}
	if (keyPressed & MOVE_UP) {
		camera->MoveUp(deltaTime);
	}

	if (keyPressed & MOVE_DOWN) {
		camera->MoveDown(deltaTime);
	}
	
	scenemanager->Update(deltaTime);
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		if (key == VK_UP)
		{
			keyPressed = keyPressed | MOVE_UP;
			return;
		}

		if (key == VK_DOWN)
		{
			keyPressed = keyPressed | MOVE_DOWN;
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
			keyPressed = keyPressed ^ MOVE_UP;
			return;
		}

		if (key == VK_DOWN)
		{
			keyPressed = keyPressed ^ MOVE_DOWN;
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
	for (int i = 0; i < scenemanager->numberOfObject; i++)
	{
		scenemanager->s_ListObject.at(i)->~Object();
	}
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