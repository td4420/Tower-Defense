#pragma once
#include "../Utilities/utilities.h"
#include <vector>
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
using namespace std;
class ResourceManager
{
public:
	static ResourceManager* s_Instance;
	char* mResourceManagerFile;
	int numberOfTexture;
	int numberOfModel;
	int numberOfShader;
	int numberOfCube;
	vector<Model*> mListModel;
	vector<Texture*> mListTexture;
	vector<Texture* > mListCube;
	vector<Shaders*> mListShaders;
	ResourceManager(char* file);
	ResourceManager();
	~ResourceManager();
	void Init();
	static ResourceManager* GetInstance(char* file);
};