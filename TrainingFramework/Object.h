#pragma once
#include "../Utilities/utilities.h"
#include <vector>
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
using namespace std;
class Object
{
public:
	int o_Id;
	Model o_Model;
	int numberOfTexture, numberOfCube;
	vector<Texture> o_Texture, o_Cube;
	Shaders o_shaders;
	Vector3 o_position, o_rotation, o_scale;
	Matrix Rx, Ry, Rz;
	Matrix Scale, Rotation, Translation;
	Matrix WorldMatrix, MVP;
	Object(Model model, vector<Texture> texture, Shaders shaders, int id = 0);
	//Object(Model model, vector<Texture> texture);
	Object();
	Object(Object* o);
	~Object();
	void InitObject();
	void DrawObject();
	void SetRotation();
	void SetWorldMatrix();
	void setMVPMatrix(Matrix v, Matrix p);
};