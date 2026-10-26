#include "Camera.h"
#include <iostream>

#include "application/tilemap/MapConstants.h"

#define PI 3.14f
#define TO_RADIANS(x) (PI / 180.0f) * x

Camera::Camera(sf::Vector2f cameraPosition, sf::Vector2f cameraRect)
	:m_CameraPosition(cameraPosition), m_CameraRect(cameraRect), m_ShakeSpeed(5.0f)
{
	m_ShakeCounter = 0.0f;
	m_CurrentShakeAmount = 0.0f;
}

void Camera::Update(float deltaTime, sf::Vector2f playerPosition, sf::Vector2f playerSize)
{
	m_CameraPosition.x = playerPosition.x + playerSize.x / 2;
	m_CameraPosition.y = playerPosition.y + playerSize.y / 2;

	if (m_CameraPosition.x - m_CameraRect.x / 2 <= 0.0f)
	{
		m_CameraPosition.x = m_CameraRect.x/2;
	}
	else if (m_CameraPosition.x + m_CameraRect.x / 2 > MapConstants::WorldWidth)
	{
		m_CameraPosition.x = MapConstants::WorldWidth - m_CameraRect.x/2;
	}

	if (m_CameraPosition.y - m_CameraRect.y / 2 <= 0.0f)
	{
		m_CameraPosition.y = m_CameraRect.y/2;
	}
	else if (m_CameraPosition.y + m_CameraRect.y / 2 > MapConstants::WorldHeight)
	{
		m_CameraPosition.y = MapConstants::WorldHeight - m_CameraRect.y / 2;
	}
}

void Camera::SetCameraVisibilityRect(sf::Vector2f cameraRect)
{
	m_CameraRect = cameraRect;
}

void Camera::ShakeCamera(float shakeAmount)
{
	m_ShakeCounter += m_ShakeSpeed;

	m_CurrentShakeAmount = std::sin(TO_RADIANS(m_ShakeCounter)) * shakeAmount;

	m_CameraPosition.x = m_CameraPosition.x + m_CurrentShakeAmount;
	m_CameraPosition.y = m_CameraPosition.y + m_CurrentShakeAmount;
}

void Camera::StopCameraShake(float shakeAmount)
{
	m_ShakeCounter = 0.0f;

	// Slowly bring the shake amount to 0
	if (m_CurrentShakeAmount > 0.0f)
	{
		m_CurrentShakeAmount -= (shakeAmount / 20.0f);

		m_CameraPosition.x = m_CameraPosition.x + m_CurrentShakeAmount;
		m_CameraPosition.y = m_CameraPosition.y + m_CurrentShakeAmount;

		std::cout << "Stopping camera shake. Current shake amount: " << m_CurrentShakeAmount << std::endl;

		if (m_CurrentShakeAmount < 0.0f)
		{
			m_CurrentShakeAmount = 0.0f;
			std::cout << "Camera shake has been stopped." << std::endl;

		}
	}else if(m_CurrentShakeAmount < 0.0f){
		m_CurrentShakeAmount += (shakeAmount / 20.0f);

		m_CameraPosition.x = m_CameraPosition.x + m_CurrentShakeAmount;
		m_CameraPosition.y = m_CameraPosition.y + m_CurrentShakeAmount;
		std::cout << "Stopping camera shake. Current shake amount: " << m_CurrentShakeAmount << std::endl;

		if (m_CurrentShakeAmount > 0.0f)
		{
			m_CurrentShakeAmount = 0.0f;
			std::cout << "Camera shake has been stopped." << std::endl;
		}
	}
}
