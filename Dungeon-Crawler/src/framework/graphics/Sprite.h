#pragma once
#include <SFML/Graphics.hpp>

#include "../graphics/Window.h"
#include "../utils/Rect.h"

class Sprite
{
private:
	sf::Sprite* m_Sprite;
	
	sf::Vector2f m_ScreenPosition, m_Size, m_Scale;
	float m_RotationAngle = 0.0f;

	Rect* m_TextureRect = nullptr;

public:
	Sprite(sf::Texture* texture, const sf::Vector2f& size);
	Sprite(sf::Texture* texture, const sf::Vector2f& size, const Rect& textureArea);
	~Sprite();

	void SetScreenPosition(const sf::Vector2f& position);
	void SetSize(const sf::Vector2f& size);
	void SetRotation(float angleInDegrees);
	
	void SetTextureRect(const Rect& rect);

	void Draw(Window* window);
	void Draw(Window* window, sf::Shader* shader);
	void DrawFlippedHorizontally(Window* window);
	void DrawFlippedHorizontally(Window* window, sf::Shader* shader);

	inline const float& GetRotationAngle() const { return m_RotationAngle; }
	inline const sf::Vector2f& GetScreenPosition() const { return m_ScreenPosition; }
	inline const sf::Vector2f& GetSize() const { return m_Size; }
	inline float GetRotationAngle() { return m_RotationAngle; }
};

