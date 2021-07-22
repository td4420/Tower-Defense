#include "stdafx.h"
#include "Object.h"
Matrix Object::SetRotation()
{
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
	Rx.SetIdentity(); Ry.SetIdentity(); Rz.SetIdentity();
	Scale.SetIdentity(); Translation.SetIdentity();
	Rotation = SetRotation();
	WorldMatrix = SetWorldMatrix();

	for (int i = 0; i <numberOfTexture; i++)
	{
		o_Texture.at(i).Init();
	}
	
}