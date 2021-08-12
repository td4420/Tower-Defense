#include "stdafx.h"
#include "Object.h"
#include <iostream>
#include "Vertex.h"
void Object::SetRotation()
{
	Rx.SetRotationX(o_rotation.x);
	Ry.SetRotationY(o_rotation.y);
	Rz.SetRotationZ(o_rotation.z);
	Rotation = Rz * Rx * Ry;
}
void Object::SetWorldMatrix()
{
	WorldMatrix = Scale * Rotation * Translation;
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
	//o_Id = 0;
}
Object::~Object()
{
	o_Model.~Model();
	for (int i = 0; i < numberOfCube; i++)
	{
		o_Cube.at(i).~Texture();
	}
	for (int i = 0; i < numberOfTexture; i++)
	{
		o_Texture.at(i).~Texture();
	}
}
void Object::setMVPMatrix(Matrix v, Matrix p)
{
	MVP = WorldMatrix * v * p;
}
void Object::InitObject()
{
	//Translation.SetIdentity();
	//Scale.SetIdentity();
	//Rotation.SetIdentity();
	//SetWorldMatrix();
	
	o_Model.Init();
	o_Texture.at(0).Init();
	for (int i = 0; i < o_Texture.size(); i++)
	{
		o_Texture.at(i).Init();
	}
	/*for (int i = 0; i < numberOfCube; i++)
	{
		o_Cube.at(i).Init();
	}*/
}
void Object::Build(float x, float y) {
	o_position.x = x ;
	o_position.y = y ;
	o_position.z = 0;

	Scale.SetIdentity();
	Rotation.SetIdentity();
	Translation.SetTranslation(o_position);
	MVP = Scale * Rotation * Translation;
}
void Object::DrawObject()
{
	glUseProgram(o_shaders.program);

	glBindTexture(GL_TEXTURE_2D, o_Texture.at(0).mTextureId);
	glBindBuffer(GL_ARRAY_BUFFER, o_Model.mVBO);
	if (o_shaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(o_shaders.positionAttribute);
		glVertexAttribPointer(o_shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (o_shaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(o_shaders.uvAttribute);
		glVertexAttribPointer(o_shaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(Vector3)));
	}

	MVP = Scale * Rotation * Translation;
	glUniformMatrix4fv(o_shaders.u_MVP, 1, GL_FALSE, *MVP.m);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o_Model.mIBO);
	glDrawElements(GL_TRIANGLES, o_Model.mNumberOfIndices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Object::Object(Object* o)
{
	o_Model = o->o_Model;
	o_Texture = o->o_Texture;
	o_shaders = o->o_shaders;
	o_Id = o->o_Id;

	o_position = o->o_position;
	o_rotation = o->o_rotation;
	o_scale = o->o_scale;
	Scale = o->Scale;
	Rotation = o->Rotation;
	Translation = o->Translation;

	Rx = o->Rx;
	Ry = o->Ry;
	Rz = o->Rz;

	Translation.SetTranslation(o->o_position);
	Rotation.SetIdentity();
	Scale.SetScale(o->o_scale);
}
