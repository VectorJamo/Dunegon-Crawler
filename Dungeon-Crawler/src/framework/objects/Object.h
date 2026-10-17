#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../utils/Rect.h"
#include "../graphics/Window.h"

#include "../graphics/Sprite.h"
#include "../entities/Animation.h"

enum class ObjectDirection
{
	IDLE = 0, UP, DOWN, LEFT, RIGHT
};

class Object
{
private:
	Sprite* m_ObjectSprite;
	AnimationComponent* m_AnimationComponent;

	sf::Vector2f m_WorldPosition;

	ObjectDirection m_CurrentDirection;
	float m_ObjectSpeed;

public:
	Object(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture);
	Object(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, Rect textureArea);
	virtual ~Object();

	void SetWorldPosition(const sf::Vector2f& position);
	void SetSize(const sf::Vector2f& size);
	void SetRotation(float angleInDegrees);
	void SetTextureRect(const Rect& textureArea);

	void SetObjectSpeed(float speed);
	void SetObjectDirection(const ObjectDirection& direction);

	void PushAnimationRect(const std::string& animationName, const Rect& animationRect);
	void PlayAnimation(const std::string& animationName);

	virtual void Update(float deltaTime);

	void Render(float cameraX, float cameraY, Window* window);
	void Render(float cameraX, float cameraY, Window* window, sf::Shader* shader);

	inline sf::Vector2f GetWorldPosition() { return m_WorldPosition; }
	inline Sprite* GetObjectSprite() { return m_ObjectSprite; } // Use this if you need the entity size, rotation angle & local screen position
	inline const ObjectDirection& GetCurrentDirection() { return m_CurrentDirection; }
	inline float GetObjectSpeed() { return m_ObjectSpeed; }
	inline AnimationComponent* GetAnimationComponent() { return m_AnimationComponent; }
};

