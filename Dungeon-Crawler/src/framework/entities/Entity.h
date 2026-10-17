#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../utils/Rect.h"
#include "../graphics/Window.h"

#include "../graphics/Sprite.h"

#include "Animation.h"

enum class EntityDirection
{
	IDLE = 0, UP, DOWN, LEFT, RIGHT
};

class Entity
{
protected:
	std::string m_Name;

	Sprite* m_EntitySprite;
	AnimationComponent* m_AnimationComponent;

	sf::Vector2f m_WorldPosition;

	EntityDirection m_CurrentDirection;
	float m_EntitySpeed;

	Rect m_CollisionRect;

public:
	Entity(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, const std::string& entityName);
	Entity(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, Rect textureArea, const std::string& entityName);
	virtual ~Entity();

	void SetWorldPosition(const sf::Vector2f& position);
	void SetSize(const sf::Vector2f& size);
	void SetRotation(float angleInDegrees);
	void SetTextureRect(const Rect& textureArea);

	void SetEntitySpeed(float speed);
	void SetEntityDirection(const EntityDirection& direction);
	void SetEntityCollisionRect(const Rect& rect);

	void PushAnimationRect(const std::string& animationName, const Rect& animationRect);
	void PlayAnimation(const std::string& animationName);

	virtual void Update(float deltaTime);
	
	void Render(float cameraX, float cameraY, Window* window);
	void Render(float cameraX, float cameraY, Window* window, sf::Shader* shader);
	void RenderFlippedHorizontally(float cameraX, float cameraY, Window* window);
	void RenderFlippedHorizontally(float cameraX, float cameraY, Window* window, sf::Shader* shader);

	inline const sf::Vector2f& GetWorldPosition() { return m_WorldPosition; }
	inline Sprite* GetEntitySprite() { return m_EntitySprite; } // Use this if you need the entity size, rotation angle & local screen position
	inline const EntityDirection& GetCurrentDirection() { return m_CurrentDirection; }
	inline float GetEntitySpeed() { return m_EntitySpeed; }
	inline const std::string& GetEntityName() const { return m_Name; }
	inline const Rect& GetEntityCollisionRect() const { return m_CollisionRect; }
};

