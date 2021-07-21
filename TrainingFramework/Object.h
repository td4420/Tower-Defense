#pragma once
#include "../Utilities/utilities.h"
class Object
{
public:
	Matrix Rx, Ry, Rz;
	Matrix Scale, Rotation, Translation;
	Matrix WorldMatrix, MVP;
	void InitObject();
	Matrix SetRotation();
	Matrix SetWorldMatrix();
};