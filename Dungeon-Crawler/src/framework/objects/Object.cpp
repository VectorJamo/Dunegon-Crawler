#include "Object.h"

Object::Object(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture)
	:m_WorldPosition(worldPosition)
{
	m_ObjectSprite = new Sprite(texture, size);

	m_AnimationComponent = new AnimationComponent();
	m_CurrentDirection = ObjectDirection::IDLE;
	m_ObjectSpeed = 100;

}

Object::Object(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, Rect textureArea)
	:m_WorldPosition(worldPosition)
{
	m_ObjectSprite = new Sprite(texture, size);
	m_ObjectSprite->SetTextureRect(textureArea);

	m_AnimationComponent = new AnimationComponent();
	m_CurrentDirection = ObjectDirection::IDLE;
	m_ObjectSpeed = 100;
}

Object::~Object()
{
	delete m_AnimationComponent;

	delete m_ObjectSprite;
}

void Object::SetWorldPosition(const sf::Vector2f& position)
{
	m_WorldPosition = position;
}

void Object::SetSize(const sf::Vector2f& size)
{
	m_ObjectSprite->SetSize(size);
}

void Object::SetRotation(float angleInDegrees)
{
	m_ObjectSprite->SetRotation(angleInDegrees);
}

void Object::SetTextureRect(const Rect& textureArea)
{
	m_ObjectSprite->SetTextureRect(textureArea);
}

void Object::SetObjectSpeed(float speed)
{
	m_ObjectSpeed = speed;

}

void Object::SetObjectDirection(const ObjectDirection& direction)
{
	m_CurrentDirection = direction;

}

void Object::PushAnimationRect(const std::string& animationName, const Rect& animationRect)
{
	m_AnimationComponent->PushAnimationRect(animationName, animationRect);

}

void Object::PlayAnimation(const std::string& animationName)
{
	m_AnimationComponent->PlayAnimation(animationName);

	Rect rect = m_AnimationComponent->GetCurrentAnimationRect(animationName);
	m_ObjectSprite->SetTextureRect(rect);
}

void Object::Update(float deltaTime)
{
}

void Object::Render(float cameraX, float cameraY, Window* window)
{
	float screenPosX = (m_WorldPosition.x) - cameraX;
	float screenPosY = (m_WorldPosition.y) - cameraY;

	m_ObjectSprite->SetScreenPosition(sf::Vector2f(screenPosX, screenPosY));
	m_ObjectSprite->Draw(window);
}

void Object::Render(float cameraX, float cameraY, Window* window, sf::Shader* shader)
{
	float screenPosX = (m_WorldPosition.x) - cameraX;
	float screenPosY = (m_WorldPosition.y) - cameraY;

	m_ObjectSprite->SetScreenPosition(sf::Vector2f(screenPosX, screenPosY));
	m_ObjectSprite->Draw(window, shader);
}
