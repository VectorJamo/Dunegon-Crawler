#pragma once
#include <SFML/Graphics.hpp>

// Position of the camera is centered to the player
class Camera
{
private:
	sf::Vector2f m_CameraPosition;
	sf::Vector2f m_CameraRect; // How much of the world you can see at once. By default, this is (screenWidth, screenHeight)

	float m_ShakeCounter;
	const float m_ShakeSpeed;
	float m_CurrentShakeAmount;

public:
	Camera(sf::Vector2f cameraPosition, sf::Vector2f cameraRect);

	void Update(float deltaTime, sf::Vector2f playerPosition, sf::Vector2f playerSize);
	void SetCameraVisibilityRect(sf::Vector2f cameraRect); 

	void ShakeCamera(float shakeAmount);
	void StopCameraShake(float shakeAmount);

	inline const sf::Vector2f& GetCameraPosition() const { return m_CameraPosition; }
	inline const sf::Vector2f& GetCameraVisibilityRect() const { return  m_CameraRect; }
};

