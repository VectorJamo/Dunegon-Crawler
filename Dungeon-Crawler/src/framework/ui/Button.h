#pragma once
#include "Text.h"

#include "framework/graphics/Window.h"

class Button
{
private:
	sf::RectangleShape m_Button;
	int32_t m_PaddingX, m_PaddingY;
	
	Text* m_Text;

	bool m_IsHovered, m_IsClicked;

private:
	void RecalculateButtonSize();
	void RecalculateTextPosition();

public:
	Button(const std::string& text, sf::Font& font);
	~Button();

	void Update(float deltaTime);
	void Render(Window* window);

	void SetPosition(const sf::Vector2f& position);
	void SetCharacterSize(int32_t size);
	void SetOutlineColor(sf::Color color);
	void SetBackgroundColor(sf::Color color);
	void SetTextColor(sf::Color color);
	
	void SetPadding(int32_t paddingX, int32_t paddingY);

	inline bool IsHovered() const { return m_IsHovered; };
	inline bool IsClicked() const { return m_IsClicked; };
	int32_t GetWidth() const;
	int32_t GetHeight() const;

};