#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"
#include "Camera.h"
class SceneManager
{
public:
	static SceneManager* s_Instance;
	Camera* camera;
	char* s_SceneManagerFile;
	int numberOfObject;
	vector<Object*> s_ListObject;
	SceneManager(char* file);
	void Init();
	void InitSceneManager();
	static SceneManager* GetInstance(char* file);
};