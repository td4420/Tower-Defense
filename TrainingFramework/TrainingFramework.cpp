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
#include "StatePlay.h"
#include "SoundController.h"

#define MOVE_FORWARD 1
#define MOVE_BACKWARD 1 << 1
#define MOVE_LEFT 1 << 2
#define MOVE_RIGHT 1 << 3
#define ROTATE_UP 1 << 4
#define ROTATE_DOWN 1 << 5
#define ROTATE_LEFT 1 << 6
#define ROTATE_RIGHT 1 << 7


int keyPressed = 0;
Shaders myShaders;

StatePlay sp = StatePlay();

int Init(ESContext* esContext)
{

	sp.Init();

	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	
}

void Draw(ESContext* esContext)
{
	sp.Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);//must have
}

void Update(ESContext* esContext, float deltaTime)
{
	sp.Update();
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	
}

bool CheckSelectionOption(int x, int y) {
	return sp.CheckSelectionOption(x, y);
}
void TouchActionDown(ESContext* esContext, int x, int y)
{
}

bool IsBuildable(int xPos, int yPos) {
	return sp.IsBuildable(xPos, yPos);
}

void TouchActionUp(ESContext* esContext, int x, int y)
{
	sp.TouchActionUp(x, y);
}
void TouchActionDrag(ESContext* esCotext, int x, int y) {
	//move drag
}
void TouchActionMove(ESContext* esContext, int x, int y)
{
	
}
void CleanUp()
{
	sp.CleanUp();
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