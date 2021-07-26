
#include "stdafx.h"
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	cubeTexture = glGetUniformLocation(program, "texture");
	u_MVP = glGetUniformLocation(program, "u_MVP");
	return 0;
}

Shaders::Shaders(char* vsFile, char* fsFile, vector<State> state)
{
	strcpy(fileVS, vsFile);
	strcpy(fileFS, fsFile);
	mShaderState = state;
}

Shaders::Shaders()
{
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}