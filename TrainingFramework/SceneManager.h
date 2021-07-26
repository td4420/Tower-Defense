#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"
#include "Camera.h"
class SceneManager
{
public:
	static SceneManager* s_Instance;
	Camera* camera = new Camera();
	char* s_SceneManagerFile;
	int numberOfObject;
	vector<Object*> s_ListObject;
	SceneManager(char* file);
	SceneManager();
	void Init();
	void InitSceneManager();
	void Update(float deltaTime);
	static SceneManager* GetInstance(char* file);
};