#include "Dwarf.h"

#include "application/AppTheme.h"
#include "framework/input/Input.h"

Dwarf::Dwarf(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, Rect textureArea, const std::string& entityName)
	:Entity(worldPosition, size, texture, textureArea, entityName)
{
	SetEntityCollisionRect(GetCollisionRectFromEntitySize(size));
	
	// Animations
	PushAnimationRect("right", { 0, 32, 32, 32 });
	PushAnimationRect("right", { 32, 32, 32, 32 });
	PushAnimationRect("right", { 32 * 2, 32, 32, 32 });
	PushAnimationRect("right", { 32 * 3, 32, 32, 32 });

	PushAnimationRect("up", { 0, 32*2, 32, 32 });
	PushAnimationRect("up", { 32, 32 * 2, 32, 32 });
	PushAnimationRect("up", { 32 * 2, 32 * 2, 32, 32 });
	PushAnimationRect("up", { 32 * 3, 32 * 2, 32, 32 });

	PushAnimationRect("down", { 0, 32 * 3, 32, 32 });
	PushAnimationRect("down", { 32, 32 * 3, 32, 32 });
	PushAnimationRect("down", { 32 * 2, 32 * 3, 32, 32 });
	PushAnimationRect("down", { 32 * 3, 32 * 3, 32, 32 });

	m_ShouldRenderFlipped = false;
	m_Health = 80.0f;
	m_EntitySpeed = 150.0f;
}

Dwarf::~Dwarf()
{
}

void Dwarf::Update(float deltaTime, Camera* camera, TileMap* baseMapLayer, TileMap* objectsMapLayer)
{
	m_ShouldRenderFlipped = false;
	m_CurrentDirection = EntityDirection::IDLE;

	if (Input::IsKeyPressed(Key::D))
	{
		m_CurrentDirection = EntityDirection::RIGHT;
	}
	else if (Input::IsKeyPressed(Key::A))
	{
		m_CurrentDirection = EntityDirection::LEFT;
	}
	else if (Input::IsKeyPressed(Key::W))
	{
		m_CurrentDirection = EntityDirection::UP;
	}
	else if (Input::IsKeyPressed(Key::S))
	{
		m_CurrentDirection = EntityDirection::DOWN;
	}

	if (!(CollisionHandler::CheckEntityWorldCollision(baseMapLayer, this, deltaTime) || CollisionHandler::CheckEntityWorldCollision(objectsMapLayer, this, deltaTime)))
	{
		switch (m_CurrentDirection)
		{
		case EntityDirection::UP:
			PlayAnimation("up");
			m_WorldPosition.y -= m_EntitySpeed * deltaTime;
			break;
		case EntityDirection::DOWN:
			PlayAnimation("down");
			m_WorldPosition.y += m_EntitySpeed * deltaTime;
			break;
		case EntityDirection::LEFT:
			PlayAnimation("right");
			m_WorldPosition.x -= m_EntitySpeed * deltaTime;

			m_ShouldRenderFlipped = true;
			break;
		case EntityDirection::RIGHT:
			PlayAnimation("right");
			m_WorldPosition.x += m_EntitySpeed * deltaTime;
			break;
		}
	}
}

void Dwarf::Render(sf::Vector2f cameraPosition, sf::Vector2f cameraRect, Window* window, bool renderCollisionRect)
{
	if (!m_ShouldRenderFlipped)
		Entity::Render(cameraPosition, cameraRect, window);
	else
		Entity::RenderFlippedHorizontally(cameraPosition, cameraRect, window);

	if (!renderCollisionRect)
		return;

	RenderCollisionRect(window);
}

void Dwarf::Render(sf::Vector2f cameraPosition, sf::Vector2f cameraRect, Window* window, bool renderCollisionRect, sf::Shader& shader)
{
	if (!m_ShouldRenderFlipped)
		Entity::Render(cameraPosition, cameraRect, window, &shader);
	else
		Entity::RenderFlippedHorizontally(cameraPosition, cameraRect, window, &shader);

	if (!renderCollisionRect)
		return;

	RenderCollisionRect(window);
}

Rect Dwarf::GetCollisionRectWorldBounds()
{
	// TODO: insert return statement here
	Rect collisionRectLocalBounds = GetCollisionRectFromEntitySize(GetEntitySprite()->GetSize());
	sf::Vector2f worldPos = { m_WorldPosition.x + collisionRectLocalBounds.x, m_WorldPosition.y + collisionRectLocalBounds.y };

	Rect collisionRectGlobalBounds;
	collisionRectGlobalBounds.x = worldPos.x;
	collisionRectGlobalBounds.y = worldPos.y;
	collisionRectGlobalBounds.width = collisionRectLocalBounds.width;
	collisionRectGlobalBounds.height = collisionRectLocalBounds.height;

	return collisionRectGlobalBounds;
}

void Dwarf::RenderCollisionRect(Window* window)
{
	sf::RectangleShape shape;
	const Rect& collisionRect = GetEntityCollisionRect();
	const sf::Vector2f& playerScreenPosition = GetEntitySprite()->GetScreenPosition();

	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(2);
	shape.setOutlineColor({ 255, 0, 0, 255 });
	shape.setSize({ (float)collisionRect.width, (float)collisionRect.height });
	shape.setPosition({ playerScreenPosition.x + collisionRect.x, playerScreenPosition.y + collisionRect.y });

	window->GetWindowInstance()->draw(shape);
}

Rect GetCollisionRectFromEntitySize(const sf::Vector2f& size)
{
	// Collision Rect for a default 32x32 texture
	Rect collisionRect = { 12, 20, 10, 10 };

	float xMultiplier = collisionRect.x / 32.0f;
	float yMultiplier = collisionRect.y / 32.0f;
	float widthMultiplier = collisionRect.width / 32.0f;
	float heightMultiplier = collisionRect.height / 32.0f;

	return Rect(xMultiplier*size.x, yMultiplier*size.y, widthMultiplier*size.x, heightMultiplier*size.y);
}
