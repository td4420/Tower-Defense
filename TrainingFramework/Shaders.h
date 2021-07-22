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
	GLint colorAttribute;
	GLint uvAttribute;
	GLint u_MVP, u_view, u_projection;
	int Init(char * fileVertexShader, char * fileFragmentShader);
	Shaders(char* vsFile, char* fsFile, vector<State> state);
	Shaders();
	~Shaders();
};