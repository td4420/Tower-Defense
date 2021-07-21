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
void Object::InitObject()
{
	Rx.SetIdentity(); Ry.SetIdentity(); Rz.SetIdentity();
	Scale.SetIdentity(); Translation.SetIdentity();
	Rotation = SetRotation();
	WorldMatrix = SetWorldMatrix();
}