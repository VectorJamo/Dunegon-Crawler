#pragma once
#include "framework/entities/Entity.h"
#include "framework/assets/AssetManager.h"
#include "framework/utils/CollisionHandler.h"

#include "application/systems/Camera.h"

class Dwarf : public Entity
{
private:
	bool m_ShouldRenderFlipped;

	float m_Health;

public:
	Dwarf(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, Rect textureArea, const std::string& entityName);
	~Dwarf();

	void Update(float deltaTime, Camera* camera, TileMap* baseMapLayer, TileMap* objectsMapLayer);

	void Render(sf::Vector2f cameraPosition, sf::Vector2f cameraRect, Window* window, bool renderCollisionRect);
	void Render(sf::Vector2f cameraPosition, sf::Vector2f cameraRect, Window* window, bool renderCollisionRect, sf::Shader& shader);

	inline float GetHealth() { return m_Health; }
	inline Rect GetCollisionRectWorldBounds();

private:
	void RenderCollisionRect(Window* window);
};

static Rect GetCollisionRectFromEntitySize(const sf::Vector2f& size);