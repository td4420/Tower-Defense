#pragma once
#include "../Utilities/utilities.h"
class Camera {
public:
	float m_far, m_near, m_FOV;
	float m_cameraSpeed = 2.0f;
	float m_rotationSpeed = 0.5f;
	Vector3 position, target;
	Vector3 xaxis, yaxis, zaxis;
	Vector3 up;
	Matrix ViewMatrix, WorldMatrix, PerspectiveMatrix;
	Matrix MVP;
	Matrix Rotation, Translation;
	void InitCamera();
	void MoveForward(float deltaTime);
	void MoveBackward(float deltaTime);
	void MoveToLeft(float deltaTime);
	void MoveToRight(float deltaTime);
	void RotationAroundX(float deltaTime);
	void RotationAroundY(float deltaTime);
	void RotationAroundZ(float deltaTime);
	void RotationUp(float deltaTime);
	void RotationDown(float deltaTime);
	void RotationLeft(float deltaTime);
	void RotationRight(float deltaTime);
	void SetRotation();
	void SetTranslation();
	void SetWorldMatrix();
	void SetViewMatrix();
	void SetPerSpectiveMatrix();
	void SetMVP();
	void Update(float deltaTime);
};