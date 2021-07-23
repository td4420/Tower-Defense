#include "stdafx.h"
#include "Object.h"
#include <iostream>
#include "Vertex.h"
Matrix Object::SetRotation()
{
	Rx.SetRotationX(o_rotation.x);
	Ry.SetRotationY(o_rotation.y);
	Rz.SetRotationZ(o_rotation.z);
	return Rz * Rx * Ry;
}
Matrix Object::SetWorldMatrix()
{
	return Scale * Rotation * Translation;
}
Object::Object(Model model, vector<Texture> texture, Shaders shaders,int id)
{
	o_Model = model;
	o_Texture = texture;
	o_shaders = shaders;
	o_Id = id;
}
Object::Object()
{

}
void Object::InitObject()
{
	Translation.SetTranslation(o_positon);
	Scale.SetScale(o_scale);
	Rotation = SetRotation();
	WorldMatrix = SetWorldMatrix();
	for (int i = 0; i <numberOfTexture; i++)
	{
		o_Texture.at(i).Init();
	}
}