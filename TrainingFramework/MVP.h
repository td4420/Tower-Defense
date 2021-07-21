#pragma once
#include "../Utilities/utilities.h"
#include "Shaders.h"
class MVP
{
public:
	Matrix w_Rx, w_Ry, w_Rz; //For world matrix
	Matrix v_Rx, v_Ry, v_Rz; //For view matrix
	Matrix w_transform, scale, w_rotation, v_rotation, v_transform;
	Matrix World, View;
	MVP();
	void Init(GLuint program);
	void RotationX(GLfloat angle);
	void RotationY(GLfloat angle);
	void RotationZ(GLfloat angle);
	void Translation(Vector3 vec);
	void Scale(GLfloat scale);
};