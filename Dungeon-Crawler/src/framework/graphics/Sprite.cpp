#include "Sprite.h"

Sprite::Sprite(sf::Texture* texture, const sf::Vector2f& size)
{
	m_Sprite = new sf::Sprite(*texture);
	m_Size = size;
	
	sf::Vector2u textureSize = texture->getSize();
	m_Scale = sf::Vector2f(size.x / (float)textureSize.x, size.y / (float)textureSize.y);
}

Sprite::Sprite(sf::Texture* texture, const sf::Vector2f& size, const Rect& textureArea)
{
	m_Sprite = new sf::Sprite(*texture);
	m_Size = size;

	m_TextureRect = new Rect(textureArea);

	m_Sprite->setTextureRect(sf::IntRect(sf::Vector2i(textureArea.x, textureArea.y), sf::Vector2i(textureArea.width, textureArea.height)));
	
	m_Scale = sf::Vector2f(size.x / (float)textureArea.width, size.y / (float)textureArea.height);
}

Sprite::~Sprite()
{
	delete m_TextureRect;

	delete m_Sprite;
}

void Sprite::SetScreenPosition(const sf::Vector2f& position)
{
	m_ScreenPosition = position;
}

void Sprite::SetSize(const sf::Vector2f& size)
{
	m_Size = size;
	if (m_TextureRect == nullptr)
	{
		sf::Vector2u textureSize = m_Sprite->getTexture().getSize();
		m_Scale = sf::Vector2f(size.x / (float)textureSize.x, size.y / (float)textureSize.y);
		return;
	}

	m_Scale = sf::Vector2f(size.x / (float)m_TextureRect->width, size.y / (float)m_TextureRect->height);
}

void Sprite::SetRotation(float angleInDegrees)
{
	m_RotationAngle = angleInDegrees;
}

void Sprite::SetTextureRect(const Rect& rect)
{
	if (m_TextureRect != nullptr)
		delete m_TextureRect;

	m_TextureRect = new Rect(rect);

	m_Sprite->setTextureRect(sf::IntRect(sf::Vector2i(rect.x, rect.y), sf::Vector2i(rect.width, rect.height)));

	m_Scale = sf::Vector2f(m_Size.x / (float)rect.width, m_Size.y / (float)rect.height);
}

void Sprite::Draw(Window* window)
{
	sf::Transform m_Transform; // Screen coordinates

	m_Transform.translate(m_ScreenPosition);
	m_Transform.rotate(sf::degrees(m_RotationAngle), sf::Vector2f(m_Size.x/2, m_Size.y/2));
	m_Transform.scale(m_Scale);

	window->GetWindowInstance()->draw(*m_Sprite, m_Transform);
}

void Sprite::Draw(Window* window, sf::Shader* shader)
{
	sf::Transform transform; // Screen coordinates

	transform.translate(m_ScreenPosition);
	transform.rotate(sf::degrees(m_RotationAngle), sf::Vector2f(m_Size.x / 2, m_Size.y / 2));
	transform.scale(m_Scale);

	sf::RenderStates renderStates;
	renderStates.transform = transform;
	renderStates.shader = shader;

	window->GetWindowInstance()->draw(*m_Sprite, renderStates);
}

void Sprite::DrawFlippedHorizontally(Window* window)
{
	sf::Transform transform; // Screen coordinates

	sf::Vector2f spriteSize = { (float)m_TextureRect->width, (float)m_TextureRect->height };

	transform.translate({ m_ScreenPosition.x + spriteSize.x*2, m_ScreenPosition.y }); // To account for the flip. Since the flip happens w.r.t the local origin (top-left).
	transform.rotate(sf::degrees(m_RotationAngle), sf::Vector2f(m_Size.x / 2, m_Size.y / 2));
	transform.scale({ -m_Scale.x, m_Scale.y });

	sf::RenderStates renderStates;
	renderStates.transform = transform;

	window->GetWindowInstance()->draw(*m_Sprite, renderStates);
}

void Sprite::DrawFlippedHorizontally(Window* window, sf::Shader* shader)
{
	sf::Transform transform; // Screen coordinates

	sf::Vector2f spriteSize = { (float)m_TextureRect->width, (float)m_TextureRect->height };

	transform.translate({ m_ScreenPosition.x + spriteSize.x * 2, m_ScreenPosition.y }); // To account for the flip. Since the flip happens w.r.t the local origin (top-left).
	transform.rotate(sf::degrees(m_RotationAngle), sf::Vector2f(m_Size.x / 2, m_Size.y / 2));
	transform.scale({ -m_Scale.x, m_Scale.y });

	sf::RenderStates renderStates;
	renderStates.transform = transform;
	renderStates.shader = shader;

	window->GetWindowInstance()->draw(*m_Sprite, renderStates);
}
