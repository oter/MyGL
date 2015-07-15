#pragma once
#include <Eigen/Dense>

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void lookAt(const Eigen::Vector3f& position, const Eigen::Vector3f& target, const Eigen::Vector3f& up);

	void setPerspective(float fovY, float aspectRatio, float nearPlane, float farPlane);

	void setOrtho(float left, float right, float bottom, float top, float zNear, float zFar);

	const Eigen::Matrix4f& getViewProjectionMatrix();

private:
	void updateViewProjectionMatrix();

private:
	Eigen::Matrix4f m_ViewMatrix;
	Eigen::Matrix4f m_ProjectionMatrix;
	Eigen::Matrix4f m_ViewProjectionMatrix;

};

