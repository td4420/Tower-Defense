#pragma once
#include "../Utilities/utilities.h"
#include "Shaders.h"
class MVP
{
public:
	Shaders myShaders;
	Matrix Rx, Ry, Rz;
	Matrix transform, scale, rotation;
	Matrix World;
	MVP(Shaders shader);
	void Init();
	void RotationX(GLfloat angle);
	void RotationY(GLfloat angle);
	void RotationZ(GLfloat angle);
	void Translation(Vector3 vec);
	void Scale(GLfloat scale);
};