#include "stdafx.h"
#include "MVP.h"
MVP::MVP(Shaders shader)
{
	myShaders = shader;
	scale.SetIdentity();
	rotation.SetIdentity();
	transform.SetIdentity();
	Rx.SetIdentity();
	Ry.SetIdentity();
	Rz.SetIdentity();
}
void MVP::RotationX(GLfloat angle)
{
	Rx.SetRotationX(angle);
}

void MVP::RotationY(GLfloat angle)
{
	Ry.SetRotationY(angle);
}

void MVP::RotationZ(GLfloat angle)
{
	Rz.SetRotationZ(angle);
}
void MVP::Scale(GLfloat s)
{
	scale.SetScale(s);
}
void MVP::Translation(Vector3 vec)
{
	transform.SetTranslation(vec);
}
void MVP::Init()
{
	rotation = Rx * Ry * Rz;
	World =scale * rotation * transform;
	GLint transformLoc = glGetUniformLocation(myShaders.program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, *World.m);
}