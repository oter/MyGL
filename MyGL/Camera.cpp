#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::lookAt(const Eigen::Vector3f& position, const Eigen::Vector3f& target, const Eigen::Vector3f& up)
{
	Eigen::Matrix3f m;
	m.col(2) = (position - target).normalized(); // camera direction vector
	m.col(0) = up.cross(m.col(2)).normalized(); // right vector
	m.col(1) = up; // up vector
	m_ViewMatrix.topLeftCorner<3, 3>() = m.transpose();
	m_ViewMatrix.topRightCorner<3, 1>() = -m.transpose() * position;
	m_ViewMatrix(3, 3) = 1.0f;

	updateViewProjectionMatrix();
}

void Camera::setPerspective(float fovY, float aspectRatio, float zNear, float zFar)
{
	float theta = fovY * 0.5f;
	float range = zFar - zNear;
	float invtan = 1.0f / tan(theta);

	m_ProjectionMatrix(0, 0) = invtan / aspectRatio;
	m_ProjectionMatrix(1, 1) = invtan;
	m_ProjectionMatrix(2, 2) = -(zNear + zFar) / range;
	m_ProjectionMatrix(3, 2) = -1;
	m_ProjectionMatrix(2, 3) = -2 * zNear * zFar / range;
	m_ProjectionMatrix(3, 3) = 0;

	updateViewProjectionMatrix();
}

void Camera::setOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_ProjectionMatrix(0, 0) = 2.0f / (right - left);
	m_ProjectionMatrix(1, 1) = 2.0f / (top - bottom);
	m_ProjectionMatrix(2, 2) = -2.0f / (zFar - zNear);
	m_ProjectionMatrix(3, 0) = -(right + left) / (right - left);
	m_ProjectionMatrix(3, 1) = -(top + bottom) / (top - bottom);
	m_ProjectionMatrix(3, 2) = -(zFar + zNear) / (zFar - zNear);
	m_ProjectionMatrix(3, 3) = 1.0f;

	updateViewProjectionMatrix();
}

const Eigen::Matrix4f& Camera::getViewProjectionMatrix()
{
	return m_ViewProjectionMatrix;
}

void Camera::updateViewProjectionMatrix()
{
	m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
}
