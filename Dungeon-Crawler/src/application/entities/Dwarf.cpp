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
}

Dwarf::~Dwarf()
{
}

void Dwarf::Update(float deltaTime, Camera* camera)
{
	m_ShouldRenderFlipped = false;

	if (Input::IsKeyPressed(Key::D))
	{
		PlayAnimation("right");
		m_WorldPosition.x += m_EntitySpeed * deltaTime;
		//camera->ShakeCamera(2.0f);
	}
	else if (Input::IsKeyPressed(Key::A))
	{
		PlayAnimation("right");
		m_WorldPosition.x -= m_EntitySpeed * deltaTime;

		m_ShouldRenderFlipped = true;
		//camera->ShakeCamera(2.0f);
	}
	else if (Input::IsKeyPressed(Key::W))

	{
		PlayAnimation("up");
		m_WorldPosition.y -= m_EntitySpeed * deltaTime;
		//camera->ShakeCamera(2.0f);
	}
	else if (Input::IsKeyPressed(Key::S))
	{
		PlayAnimation("down");
		m_WorldPosition.y += m_EntitySpeed * deltaTime;
		//camera->ShakeCamera(2.0f);
	}
	else {
		//camera->StopCameraShake(2.0f);
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
	Rect collisionRect = { 8, 16, 16, 16 };

	float xMultiplier = 8.0f / 32.0f;
	float yMultiplier = 16.0f / 32.0f;
	float widthMultiplier = 16.0f / 32.0f;
	float heightMultiplier = 16.0f / 32.0f;

	return Rect(xMultiplier*size.x, yMultiplier*size.y, widthMultiplier*size.x, heightMultiplier*size.y);
}
