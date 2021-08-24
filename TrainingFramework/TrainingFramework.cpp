#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <iostream>
#include "SceneManager.h"
#include "ResourceManager.h"
#include"Text.h"
#include"StateMenu.h"
#include"StateBase.h"
#include"StateWelcome.h"
#include"StatePlay.h"
#include"Game.h"
using namespace std;

#define MOVE_FORWARD 1
#define MOVE_BACKWARD 1 << 1
#define MOVE_LEFT 1 << 2
#define MOVE_RIGHT 1 << 3
#define ROTATE_UP 1 << 4
#define ROTATE_DOWN 1 << 5
#define ROTATE_LEFT 1 << 6
#define ROTATE_RIGHT 1 << 7


int keyPressed = 0;
SceneManager* scenemanager = SceneManager::GetInstance("../ResourcesPacket/SM.txt");
Shaders* myShaders = new Shaders();
Shaders* textShader = new Shaders();
Camera* camera;
Vector4 color(0.0, 0.3, 0.3, 0.8);
//StateMenu* myStateMenu = new StateMenu();
//StateWelcome* myStateWelcome = new StateWelcome();
Game* myGame = new Game();
//StateWelcome* stateWelcome = new StateWelcome();
//StatePlay* statePlay = new StatePlay();
int Init(ESContext* esContext)
{
	
	//glEnable(GL_DEPTH_TEST);
	
	
	//creation of shaders and program 
	//myButton->init();
	//myStateMenu->init();
	//stateWelcome->init();
	//statePlay->init();
	myGame->init();
	
	//myShaders = scenemanager->s_ListObject.at(0)->o_shaders;
	myShaders->Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	return textShader->Init("../Resources/Shaders/Text.vs", "../Resources/Shaders/Text.fs");

}
void Draw(ESContext* esContext)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//scenemanager->Draw();
	//myButton->Draw(myShaders);
	//myStateMenu->Draw(textShader);
	//myStateWelcome->Draw(myShaders);
	//myStateWelcome->Drawtext(textShader);
	//stateWelcome->Draw(textShader, myShaders);
	//myStateMenu->DrawLogo(myShaders);
	//statePlay->Draw();
	myGame->Draw(textShader,myShaders);
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
	if (keyPressed & ROTATE_UP) {
		camera->RotationUp(deltaTime);
	}

	if (keyPressed & ROTATE_DOWN) {
		camera->RotationDown(deltaTime);
	}
	if (keyPressed & ROTATE_LEFT) {
		camera->RotationLeft(deltaTime);
	}
	if (keyPressed & ROTATE_RIGHT) {
		camera->RotationRight(deltaTime);
	}
	scenemanager->Update(deltaTime);
	//stateWelcome->Update(deltaTime);
	//statePlay->Update();
	myGame->Update(deltaTime);
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

void TouchActionDown(ESContext* esContext, int x, int y)
{
	myGame->OnMouseClick(x, y);
	//stateWelcome->OnMouseClick(x,y);
	//statePlay->OnMouseClick(x,y);
	printf("\n: mouse down at: %d, %d", x, y);
}

void TouchActionUp(ESContext* esContext, int x, int y)
{
	//myGame->OnMouseClick(x, y);
	printf("\n: mouse up at: %d, %d", x, y);
}
void TouchActionDrag(ESContext* esCotext, int x, int y) {
	//move drag
	printf("\n mouse when drag: %d, %d", x, y);
}

void TouchActionMove(ESContext* esContext, int x, int y)
{
	myGame->OnMouseOver(x,y);

	//stateWelcome->OnMouseOver(x, y);

}
void CleanUp()
{
	myGame->statePlay->CleanUp();
}
int _tmain(int argc, TCHAR* argv[])
{
	//glViewport(0, 0, Globals::screenWidth, Globals::screenHeight);
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Tower Defense", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

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