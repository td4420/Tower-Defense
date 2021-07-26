#pragma once
#include "../Utilities/utilities.h"
#include <vector>
#include "State.h"
using namespace std;
class Shaders 
{
public:
	int ID;
	vector<State> mShaderState;
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint cubeTexture;
	GLint u_MVP;
	int Init(char * fileVertexShader, char * fileFragmentShader);
	Shaders(char* vsFile, char* fsFile, vector<State> state);
	Shaders();
	~Shaders();
};