#include "Entity.h"

#define PI 3.1415f

Entity::Entity(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, const std::string& entityName)
	:m_Name(entityName), m_WorldPosition(worldPosition)
{
	m_EntitySprite = new Sprite(texture, size);

	m_AnimationComponent = new AnimationComponent();
	m_CurrentDirection = EntityDirection::IDLE;
	m_EntitySpeed = 100;
	m_CollisionRect = { 0, 0, (int32_t)size.x, (int32_t)size.y };
}

Entity::Entity(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, Rect textureArea, const std::string& entityName)
	:m_Name(entityName), m_WorldPosition(worldPosition)
{
	m_EntitySprite = new Sprite(texture, size);
	m_EntitySprite->SetTextureRect(textureArea);

	m_AnimationComponent = new AnimationComponent();
	m_CurrentDirection = EntityDirection::IDLE;
	m_EntitySpeed = 100;
	m_CollisionRect = { 0, 0, (int32_t)size.x, (int32_t)size.y };
}

Entity::~Entity()
{
	delete m_AnimationComponent;
	
	delete m_EntitySprite;
}

void Entity::SetWorldPosition(const sf::Vector2f& position)
{
	m_WorldPosition = position;
}

void Entity::SetSize(const sf::Vector2f& size)
{
	m_EntitySprite->SetSize(size);
}

void Entity::SetRotation(float angleInDegrees)
{
	m_EntitySprite->SetRotation(angleInDegrees);
}

void Entity::SetTextureRect(const Rect& textureArea)
{
	m_EntitySprite->SetTextureRect(textureArea);
}

void Entity::SetEntitySpeed(float speed)
{
	m_EntitySpeed = speed;
}

void Entity::SetEntityDirection(const EntityDirection& direction)
{
	m_CurrentDirection = direction;
}

void Entity::SetEntityCollisionRect(const Rect& rect)
{
	m_CollisionRect = rect;
}

void Entity::PushAnimationRect(const std::string& animationName, const Rect& animationRect)
{
	m_AnimationComponent->PushAnimationRect(animationName, animationRect);
}

void Entity::PlayAnimation(const std::string& animationName)
{
	m_AnimationComponent->PlayAnimation(animationName);

	Rect rect = m_AnimationComponent->GetCurrentAnimationRect(animationName);
	m_EntitySprite->SetTextureRect(rect);
}

void Entity::Update(float deltaTime)
{
}

void Entity::Render(float cameraX, float cameraY, Window* window)
{
	float screenPosX = (m_WorldPosition.x) - cameraX;
	float screenPosY = (m_WorldPosition.y) - cameraY;

	m_EntitySprite->SetScreenPosition(sf::Vector2f(screenPosX, screenPosY));
	m_EntitySprite->Draw(window);
}

void Entity::Render(float cameraX, float cameraY, Window* window, sf::Shader* shader)
{
	float screenPosX = (m_WorldPosition.x) - cameraX;
	float screenPosY = (m_WorldPosition.y) - cameraY;

	m_EntitySprite->SetScreenPosition(sf::Vector2f(screenPosX, screenPosY));
	m_EntitySprite->Draw(window, shader);
}

void Entity::RenderFlippedHorizontally(float cameraX, float cameraY, Window* window)
{
	float screenPosX = (m_WorldPosition.x) - cameraX;
	float screenPosY = (m_WorldPosition.y) - cameraY;

	m_EntitySprite->SetScreenPosition(sf::Vector2f(screenPosX, screenPosY));
	m_EntitySprite->DrawFlippedHorizontally(window);
}

void Entity::RenderFlippedHorizontally(float cameraX, float cameraY, Window* window, sf::Shader* shader)
{
	float screenPosX = (m_WorldPosition.x) - cameraX;
	float screenPosY = (m_WorldPosition.y) - cameraY;

	m_EntitySprite->SetScreenPosition(sf::Vector2f(screenPosX, screenPosY));
	m_EntitySprite->DrawFlippedHorizontally(window, shader);
}
