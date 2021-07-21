#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
void Camera::InitCamera()
{
	m_far = 100.0f; m_near = 0.1f; m_FOV = 0.5f;
	position = Vector3(0.0f, 0.0f, -5.0f);
	target = Vector3(0.0f, 0.0f, -1.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);
	zaxis = (position - target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
	SetWorldMatrix();
	SetViewMatrix();
	SetPerSpectiveMatrix();
}
void Camera::SetRotation()
{
	Rotation.m[0][0] = xaxis.x; Rotation.m[0][1] = xaxis.y; Rotation.m[0][2] = xaxis.z; Rotation.m[0][3] = 0;
	Rotation.m[1][0] = yaxis.x; Rotation.m[1][1] = yaxis.y; Rotation.m[1][2] = yaxis.z; Rotation.m[1][3] = 0;
	Rotation.m[2][0] = zaxis.x; Rotation.m[2][1] = zaxis.y; Rotation.m[2][2] = zaxis.z; Rotation.m[2][3] = 0;
	Rotation.m[3][0] = 0; Rotation.m[3][1] = 0; Rotation.m[3][2] = 0; Rotation.m[3][3] = 1;
}
void Camera::SetTranslation()
{
	Translation.m[0][0] = 1; Translation.m[0][1] = 0; Translation.m[0][2] = 0; Translation.m[0][3] = 0;
	Translation.m[1][0] = 0; Translation.m[1][1] = 1; Translation.m[1][2] = 0; Translation.m[1][3] = 0;
	Translation.m[2][0] = 0; Translation.m[2][1] = 0; Translation.m[2][2] = 1; Translation.m[2][3] = 0;
	Translation.m[3][0] = position.x; Translation.m[3][1] = position.y; Translation.m[3][2] = position.z; Translation.m[3][3] = 1;
}
void Camera::SetWorldMatrix()
{
	WorldMatrix = Rotation * Translation;
}
void Camera::SetViewMatrix()
{
	ViewMatrix.m[0][0] = xaxis.x; ViewMatrix.m[0][1] = yaxis.x; ViewMatrix.m[0][2] = zaxis.x; ViewMatrix.m[0][3] = 0;
	ViewMatrix.m[1][0] = xaxis.y; ViewMatrix.m[1][1] = yaxis.y; ViewMatrix.m[1][2] = zaxis.y; ViewMatrix.m[1][3] = 0;
	ViewMatrix.m[2][0] = xaxis.z; ViewMatrix.m[2][1] = yaxis.z; ViewMatrix.m[2][2] = zaxis.z; ViewMatrix.m[2][3] = 0;
	ViewMatrix.m[3][0] = -position.Dot(xaxis); ViewMatrix.m[3][1] = -position.Dot(yaxis); ViewMatrix.m[3][2] = -position.Dot(zaxis); ViewMatrix.m[3][3] = 1;
}
void Camera::SetPerSpectiveMatrix()
{
	float aspect = float(Globals::screenWidth) / float(Globals::screenHeight);
	PerspectiveMatrix.SetPerspective(m_FOV, aspect, m_near, m_far);
}
void Camera::SetMVP()
{
	MVP = WorldMatrix * ViewMatrix * PerspectiveMatrix;
}
void Camera::MoveForward(float deltaTime)
{
	Vector3 deltaMove = -(position - target).Normalize() * deltaTime * m_cameraSpeed;
	position += deltaMove;
	target += deltaMove;
}
void Camera::MoveBackward(float deltaTime)
{
	Vector3 deltaMove = -(position - target).Normalize() * deltaTime * m_cameraSpeed;
	position -= deltaMove;
	target -= deltaMove;	
}
void Camera::MoveToLeft(float deltaTime)
{
	Vector3 deltaMove = -(up.Cross(zaxis)).Normalize() * deltaTime * m_cameraSpeed;
	position += deltaMove;
	target += deltaMove;
	
}
void Camera::MoveToRight(float deltaTime)
{
	Vector3 deltaMove = -(up.Cross(zaxis)).Normalize() * deltaTime * m_cameraSpeed;
	position -= deltaMove;
	target -= deltaMove;
	
}
void Camera::RotationAroundX(float deltaTime)
{
	Matrix view = ViewMatrix;
	float angle = deltaTime * m_rotationSpeed;
	view.SetRotationX(angle);
	Vector4 localTarget = Vector4(0, 0, -(position - target).Length(), 1);
	Vector4 localNewTarget = localTarget * view;
	Vector4 worldNewTarget = localNewTarget * WorldMatrix;
	target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}
void Camera::RotationAroundY(float deltaTime)
{
	Vector4 rotationAxis = Vector4(0, 1, 0, 0) * ViewMatrix;
	Matrix rotation;
	rotation.SetIdentity();
	float angle = deltaTime * m_rotationSpeed;
	rotation.SetRotationAngleAxis(angle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
	Vector4 localTarget = Vector4(0, 0, -(position - target).Length(), 1);
	Vector4 localNewTarget = localTarget * rotation;
	Vector4 worldNewTarget = localNewTarget * WorldMatrix;
	target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}
void Camera::RotationAroundZ(float deltaTime)
{
	Matrix view = ViewMatrix;
	float angle = deltaTime * m_rotationSpeed;
	view.SetRotationZ(angle);
	Vector4 localTarget = Vector4(0, 0, -(position - target).Length(), 1);
	Vector4 localNewTarget = localTarget * view;
	Vector4 worldNewTarget = localNewTarget * WorldMatrix;
	target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}
void Camera::RotationUp(float deltaTime)
{
	RotationAroundX(deltaTime);
}
void Camera::RotationDown(float deltaTime)
{
	RotationAroundX(-deltaTime);
}
void Camera::RotationLeft(float deltaTime)
{
	RotationAroundY(deltaTime);
}
void Camera::RotationRight(float deltaTime)
{
	RotationAroundY(-deltaTime);
}
void Camera::Update(float deltaTime)
{
	zaxis = (position - target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();

	SetRotation();
	SetTranslation();
	SetWorldMatrix();
	SetViewMatrix();
	SetMVP();
}