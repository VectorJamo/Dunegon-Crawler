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

	bool m_ShouldMove, m_HasTorch, m_HasAxe;
	bool m_IsAttacking;

public:
	Dwarf(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, Rect textureArea, const std::string& entityName);
	~Dwarf();

	void SetHasTorch(bool value);
	void SetHasAxe(bool value);

	void Update(float deltaTime, Camera* camera, TileMap* baseMapLayer, TileMap* objectsMapLayer);

	void Render(sf::Vector2f cameraPosition, sf::Vector2f cameraRect, Window* window, bool renderCollisionRect);
	void Render(sf::Vector2f cameraPosition, sf::Vector2f cameraRect, Window* window, bool renderCollisionRect, sf::Shader& shader);

	inline float GetHealth() { return m_Health; }
	inline Rect GetCollisionRectWorldBounds();

	inline bool HasTorch() const { return m_HasTorch; }
	inline bool HasAxe() const { return m_HasAxe; }

private:
	void RenderCollisionRect(Window* window);
};

static Rect GetCollisionRectFromEntitySize(const sf::Vector2f& size);