#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"
class Camera : public Object {
public:
	int c_Id;
	float m_far, m_near, m_FOV;
	float m_cameraSpeed = 2.0f;
	float m_rotationSpeed = 0.5f;
	Vector3 position, target;
	Vector3 xaxis, yaxis, zaxis;
	Vector3 up;
	Matrix ViewMatrix, WorldMatrix, PerspectiveMatrix;
	Matrix MVP;
	Matrix Rotation, Translation;
	Camera();
	~Camera();
	void InitCamera();
	void MoveForward(float deltaTime);
	void MoveBackward(float deltaTime);
	void MoveToLeft(float deltaTime);
	void MoveToRight(float deltaTime);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);

	void SetTranslation();
	void SetWorldMatrix();
	void SetViewMatrix();
	void SetPerSpectiveMatrix();
	void Update(float deltaTime);
};