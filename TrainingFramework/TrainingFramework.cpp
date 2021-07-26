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
SceneManager* scenemanager = SceneManager::GetInstance("../ResourcesPacket/SM.txt");
Texture* cube;
Model* model;
Object* object;
Shaders myShaders;
Camera* camera;
GLuint textureId;
int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	scenemanager->Init();
	camera = scenemanager->camera;
	model = new Model("../ResourcesPacket/Models/SkyBox.nfg");
	model->Init();
	vector<char*> data;
	int iWidth = 512;
	int iHeight = 512;
	int iBpp = 0;
	char* image1 = LoadTGA(("../ResourcesPacket/Skybox Textures/right.tga"), &iWidth, &iHeight, &iBpp);
	char* image2 = LoadTGA(("../ResourcesPacket/Skybox Textures/left.tga"), &iWidth, &iHeight, &iBpp);
	char* image3 = LoadTGA(("../ResourcesPacket/Skybox Textures/top.tga"), &iWidth, &iHeight, &iBpp);
	char* image4 = LoadTGA(("../ResourcesPacket/Skybox Textures/bottom.tga"), &iWidth, &iHeight, &iBpp);
	char* image5 = LoadTGA(("../ResourcesPacket/Skybox Textures/back.tga"), &iWidth, &iHeight, &iBpp);
	char* image6 = LoadTGA(("../ResourcesPacket/Skybox Textures/front.tga"), &iWidth, &iHeight, &iBpp);
	data.push_back(image1);
	data.push_back(image2);
	data.push_back(image3);
	data.push_back(image4);
	data.push_back(image5);
	data.push_back(image6);
	GLenum format = (iBpp == 24 ? GL_RGB : GL_RGBA);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	for (int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, iWidth, iHeight, 0, format, GL_UNSIGNED_BYTE, data.at(i));
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	//creation of shaders and program 
	//myShaders = scenemanager->s_ListObject.at(0)->o_shaders;
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void Draw(ESContext* esContext)
{

	object = scenemanager->s_ListObject.at(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(myShaders.program);
	glBindBuffer(GL_ARRAY_BUFFER, model->mVBO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	if (myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	glUniform1i(myShaders.cubeTexture, 0);
	glUniformMatrix4fv(myShaders.u_MVP, 1, GL_FALSE, *object->MVP.m);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->mIBO);
	glDrawElements(GL_TRIANGLES, model->mNumberOfIndices, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
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
	scenemanager->Update(deltaTime);
	
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
	model->~Model();
	model = NULL;
	delete model;
	//texture->~Texture();
	//texture = NULL;
	//delete texture;
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