#include "stdafx.h"
#include "MVP.h"
MVP::MVP()
{
	scale.SetIdentity();
	w_rotation.SetIdentity(); v_rotation.SetIdentity();
	w_transform.SetIdentity(); w_transform.SetIdentity();
	v_Rx.SetIdentity(); w_Rx.SetIdentity();
	v_Ry.SetIdentity();	w_Ry.SetIdentity();
	v_Rz.SetIdentity(); w_Rz.SetIdentity();
}
void MVP::RotationX(GLfloat angle)
{
	w_Rx.SetRotationX(angle);
	v_Rx.SetRotationX(-angle);
}

void MVP::RotationY(GLfloat angle)
{
	w_Ry.SetRotationY(angle);
	v_Rx.SetRotationY(-angle);
}

void MVP::RotationZ(GLfloat angle)
{
	w_Rz.SetRotationZ(angle);
	v_Rz.SetRotationZ(-angle);
}
void MVP::Scale(GLfloat s)
{
	scale.SetScale(s);
}
void MVP::Translation(Vector3 vec)
{
	w_transform.SetTranslation(vec);
	v_transform.SetTranslation(Vector3(0, 0, 0) - vec);
}
void MVP::Init(GLuint program)
{
	w_rotation = w_Rx * w_Ry * w_Rz;
	World =scale * w_rotation * w_transform;
	View = v_transform * v_rotation;
	GLint transformLoc = glGetUniformLocation(program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, *World.m);
}