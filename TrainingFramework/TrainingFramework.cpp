// TrainingFramework.cpp : Defines the entry point for the console application.
//
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
#define ROTATE_UP 1 << 4
#define ROTATE_DOWN 1 << 5
#define ROTATE_LEFT 1 << 6
#define ROTATE_RIGHT 1 << 7


int keyPressed = 0;

Texture* texture;
Model* model;
Object* object;

Shaders myShaders;
Camera* camera;
int Init(ESContext* esContext)
{
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	SceneManager* scenemanager = SceneManager::GetInstance("../ResourcesPacket/SM.txt");
	scenemanager->InitSceneManager();
	//Texture
	//texture = new Texture("../ResourcesPacket/Textures/Woman1.tga");
	texture = &scenemanager->s_ListObject.at(0)->o_Texture.at(0);
	texture->Init();

	//Model
	//model = new Model("../ResourcesPacket/Models/Woman1.nfg");
	model = &scenemanager->s_ListObject.at(0)->o_Model;
	model->Init();
	//Object
	//object = new Object();
	object = scenemanager->s_ListObject.at(0);
	object->InitObject();
	//Camera
	//camera = new Camera();
	camera = scenemanager->camera;
	camera->InitCamera();
	//scenemanager->Init();
	//creation of shaders and program 
	myShaders = scenemanager->s_ListObject.at(0)->o_shaders;
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	//return myShaders.Init(myShaders.fileVS,myShaders.fileFS);
}

void Draw(ESContext* esContext)
{
	glUseProgram(myShaders.program);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture->mTextureId);
	//glBindTexture(GL_TEXTURE_2D, scenemanager->s_ListObject.at(0)->o_Texture.at(0).mTextureId);
	glBindBuffer(GL_ARRAY_BUFFER, model->mVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, scenemanager->s_ListObject.at(0)->o_Model.mVBO);
	if (myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (myShaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.uvAttribute);
		glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(Vector3)));
	}
	glUniformMatrix4fv(myShaders.u_MVP, 1, GL_FALSE, *object->WorldMatrix.m);
	glUniformMatrix4fv(myShaders.u_projection, 1, GL_FALSE, *camera->PerspectiveMatrix.m);
	glUniformMatrix4fv(myShaders.u_view, 1, GL_FALSE, *camera->ViewMatrix.m);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->mIBO);
	//glBindBuffer(GL_ARRAY_BUFFER, scenemanager->s_ListObject.at(0)->o_Model.mVBO);
	glDrawElements(GL_TRIANGLES, model->mNumberOfIndices, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
	camera->Update(deltaTime);
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
		if ( key == 'D') 
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
	model->~Model();
	model = NULL;
	delete model;
	texture->~Texture();
	texture = NULL;
	delete texture;
	object = NULL;
	delete object;
	camera = NULL;
	delete camera;
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