#include "stdafx.h"
#include "ResourceManager.h"
#include <string>
#include <iostream>
ResourceManager* ResourceManager::s_Instance = NULL;
ResourceManager::ResourceManager(char* file)
{
	mResourceManagerFile = file;
}
ResourceManager::ResourceManager()
{

}
ResourceManager* ResourceManager::GetInstance(char* file)
{
	if (!s_Instance)
		s_Instance = new ResourceManager(file);
	return s_Instance;
}
void ResourceManager::Init()
{
	FILE* file = fopen(mResourceManagerFile, "r");
	//Model
	fscanf(file, "#Models: %d\n", &numberOfModel);

	char modelFile[50];
	int modelID;
	for (int i = 0; i < numberOfModel; i++)
	{
		fscanf(file, "ID %d\n", &modelID);
		fscanf(file, "FILE %s\n", &modelFile);
		Model* model = new Model(modelFile, modelID);
		mListModel.push_back(model);
	}
	fscanf(file, "\n");
	//Texture
	int textureID;
	char textureFile[250];
	char wrap[50], filter1[50], filter2[50];
	fscanf(file, "#2D Textures: %d\n", &numberOfTexture);
	for (int i = 0; i < numberOfTexture; i++)
	{
		fscanf(file, "ID %d\n", &textureID);
		fscanf(file, "FILE %s\n", textureFile);
		fscanf(file, "WRAP %s\n", &wrap);
		fscanf(file, "FILTER %s %s\n", &filter1, &filter2);
		mListTexture.push_back(new Texture(textureFile, textureID, GL_REPEAT, GL_LINEAR, GL_LINEAR));
	}
	fscanf(file, "\n");
	//Shaders
	int shadersID, numberOfState;
	char fileVS[50], fileFS[50];
	vector<State> listState;
	char state[50];
	int isEnable;
	fscanf(file, "#Shaders: %d\n", &numberOfShader);

	for (int i = 0; i < numberOfShader; i++)
	{
		fscanf(file, "ID %d\n", &shadersID);
		fscanf(file, "VS %s\n", &fileVS);
		fscanf(file, "FS %s\n", &fileFS);
		fscanf(file, "STATES %d\n", &numberOfState);
		for (int j = 0; j < numberOfState; j++)
		{
			fscanf(file, "%c %d\n", &state, &isEnable);
			State st;
			st.glState = GLenum(state);
			st.isEnable = isEnable;
			listState.push_back(st);
		}
		mListShaders.push_back(new Shaders(fileVS, fileFS, listState));
	}
}
ResourceManager::~ResourceManager()
{
	s_Instance = NULL;
	delete s_Instance;
}