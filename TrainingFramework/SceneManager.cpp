#include "stdafx.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <iostream>
SceneManager* SceneManager::s_Instance = NULL;
SceneManager::SceneManager(char* file)
{
	s_SceneManagerFile = file;
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
		Camera* cam = new Camera();
		fscanf(file, "ID %d\n", &cam->c_Id);
		fscanf(file, "POSITION %f %f %f\n", &cam->position.x, &cam->position.y, &cam->position.z);
		fscanf(file, "TARGET %f %f %f\n", &cam->target.x, &cam->target.y, &cam->target.z);
		fscanf(file, "UP %f %f %f\n", &cam->up.x, &cam->up.y, &cam->up.z);
		fscanf(file, "FOVY %f\n", &cam->m_FOV);
		fscanf(file, "NEAR %f\n", &cam->m_near);
		fscanf(file, "FAR %f\n", &cam->m_far);
		fscanf(file, "MOVE_SPEED %f\n", &cam->m_cameraSpeed);
		fscanf(file, "ROTATE_SPEED %f\n", &cam->m_rotationSpeed);
		camera = cam;
	}
	fscanf(file, "\n");

	//Object
	ResourceManager* resource = new ResourceManager("../ResourcesPacket/RM.txt");
	resource->Init();
	std::cout << resource->mListModel.back()->mModelFile << std::endl;
	std::cout << resource->mListShaders.back()->fileFS << std::endl;

	fscanf(file, "#Objects: %d\n", &numberOfObject);
	for (int i = 0; i < numberOfObject; i++)
	{
		Object* ob = new Object();
		int modelId, idTexture, idShader;
		fscanf(file, "ID %d\n", &ob->o_Id);
		fscanf(file, "MODEL %d\n", &modelId);
		ob->o_Model = *resource->mListModel.at(modelId);
		fscanf(file, "TEXTURES %d\n", &ob->numberOfTexture);
		for (int j = 0; j < ob->numberOfTexture; j++)
		{
			fscanf(file, "TEXTURE %d\n", &idTexture);
			ob->o_Texture.push_back(*resource->mListTexture.at(idTexture));
		}
		fscanf(file, "SHADER %d\n", &idShader);
		ob->o_shaders = *resource->mListShaders.at(idShader);
		fscanf(file, "POSITION %f %f %f\n", &ob->o_positon.x, &ob->o_positon.y, &ob->o_positon.z);
		fscanf(file, "ROTATION %f %f %f\n", &ob->o_rotation.x, &ob->o_rotation.y, &ob->o_rotation.z);
		fscanf(file, "SCALE %f %f %f\n", &ob->o_scale.x, &ob->o_scale.y, &ob->o_scale.z);
		s_ListObject.push_back(ob);
		fscanf(file, "\n");
	}
}
void SceneManager::Init()
{
	InitSceneManager();
	//Init Object
	for (int i = 0; i < numberOfObject; i++)
	{
		s_ListObject.at(i)->InitObject();
		s_ListObject.at(i)->o_Model.Init();
		s_ListObject.at(i)->o_shaders.Init(s_ListObject.at(i)->o_shaders.fileVS, s_ListObject.at(i)->o_shaders.fileFS);
	}
	//Init camera
	camera->InitCamera();
}