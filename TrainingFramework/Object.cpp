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
	o_Id = 0;
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
	Translation.SetTranslation(o_position);
	Scale.SetScale(o_scale);
	SetRotation();
	SetWorldMatrix();
	for (int i = 0; i < numberOfTexture; i++)
	{
		o_Texture.at(i).Init();
	}
	for (int i = 0; i < numberOfCube; i++)
	{
		o_Cube.at(i).Init();
	}
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
	glUniformMatrix4fv(o_shaders.u_MVP, 1, GL_FALSE, *MVP.m);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o_Model.mIBO);
	glDrawElements(GL_TRIANGLES, o_Model.mNumberOfIndices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
