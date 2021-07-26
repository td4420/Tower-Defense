#include "stdafx.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <iostream>
SceneManager* SceneManager::s_Instance = NULL;
SceneManager::SceneManager(char* file)
{
	s_SceneManagerFile = file;
}

SceneManager::SceneManager()
{
}

SceneManager* SceneManager::GetInstance(char* file)
{
	if (!s_Instance)
		s_Instance = new SceneManager(file);
	return s_Instance;
}

void SceneManager::InitSceneManager()
{
	int numberOfCam;
	FILE* file = fopen(s_SceneManagerFile, "r");
	if (file == NULL)
	{
		std::cout << "No file found" << std::endl;
		return;
	}
	else std::cout << "File opened" << std::endl;
	//Camera
	fscanf(file, "#Cameras: %d\n", &numberOfCam);
	for (int i = 0; i < numberOfCam; i++)
	{
		fscanf(file, "ID %d\n", &camera->c_Id);
		fscanf(file, "POSITION %f %f %f\n", &camera->position.x, &camera->position.y, &camera->position.z);
		fscanf(file, "TARGET %f %f %f\n", &camera->target.x, &camera->target.y, &camera->target.z);
		fscanf(file, "UP %f %f %f\n", &camera->up.x, &camera->up.y, &camera->up.z);
		fscanf(file, "FOVY %f\n", &camera->m_FOV);
		fscanf(file, "NEAR %f\n", &camera->m_near);
		fscanf(file, "FAR %f\n", &camera->m_far);
		fscanf(file, "MOVE_SPEED %f\n", &camera->m_cameraSpeed);
		fscanf(file, "ROTATE_SPEED %f\n", &camera->m_rotationSpeed);
	}
	fscanf(file, "\n");

	//Object
	ResourceManager* resource = new ResourceManager("../ResourcesPacket/RM.txt");
	resource->Init();

	fscanf(file, "#Objects: %d\n", &numberOfObject);
	for (int i = 0; i < numberOfObject; i++)
	{
		Object* ob = new Object();
		int modelId, idTexture,idCube, idShader;
		fscanf(file, "ID %d\n", &ob->o_Id);
		fscanf(file, "MODEL %d\n", &modelId);
		ob->o_Model = *resource->mListModel.at(modelId);
		fscanf(file, "TEXTURES %d\n", &ob->numberOfTexture);
		for (int j = 0; j < ob->numberOfTexture; j++)
		{
			fscanf(file, "TEXTURE %d\n", &idTexture);
			ob->o_Texture.push_back(*resource->mListTexture.at(idTexture));
		}
		fscanf(file, "CUBETEXTURES %d\n",&ob->numberOfCube);
		for (int j = 0; j < ob->numberOfCube; j++)
		{
			fscanf(file, "TEXTURE %d\n", &idCube);
			ob->o_Cube.push_back(*resource->mListCube.at(idCube));
		}
		fscanf(file, "SHADER %d\n", &idShader);
		ob->o_shaders = *resource->mListShaders.at(idShader);
		fscanf(file, "POSITION %f %f %f\n", &ob->o_positon.x, &ob->o_positon.y, &ob->o_positon.z);
		fscanf(file, "ROTATION %f %f %f\n", &ob->o_rotation.x, &ob->o_rotation.y, &ob->o_rotation.z);
		fscanf(file, "SCALE %f %f %f\n", &ob->o_scale.x, &ob->o_scale.y, &ob->o_scale.z);
		s_ListObject.push_back(ob);
	}
	delete resource;
}
void SceneManager::Update(float deltaTime)
{
	camera->Update(deltaTime);
	for (int i = 0; i < numberOfObject; i++)
	{
		s_ListObject.at(i)->MVP = s_ListObject.at(i)->setMVPMatrix(camera->ViewMatrix,camera->PerspectiveMatrix);
	}
}
void SceneManager::Init()
{
	InitSceneManager();
	//Init camera
	camera->InitCamera();
	//Init Object
	for (int i = 0; i < numberOfObject; i++)
	{
		s_ListObject.at(i)->InitObject();
		s_ListObject.at(i)->o_Model.Init();
		s_ListObject.at(i)->MVP = s_ListObject.at(i)->setMVPMatrix(camera->ViewMatrix,camera->PerspectiveMatrix);
		s_ListObject.at(i)->o_shaders.Init(s_ListObject.at(i)->o_shaders.fileVS, s_ListObject.at(i)->o_shaders.fileFS);
	}

}