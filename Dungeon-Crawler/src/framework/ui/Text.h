#pragma once
#include "../graphics/Window.h"
#include <iostream>

class Text
{
private:
	sf::Text* m_Text;
	sf::Font& m_Font; 

	std::string m_String;
	sf::Vector2f m_Position;

public:
	Text(sf::Font& font);
	Text(sf::Font& font, const std::string& string);
	Text(sf::Font& font, const std::string& string, const sf::Vector2f& position);
	~Text();

	void SetPosition(sf::Vector2f position);

	void SetString(const std::string& string);
	void SetCharacterSize(int32_t sizeInPixels);
	void SetFillColor(sf::Color color);
	void SetTextStyle(sf::Text::Style style);

	void Render(Window* window);

	int32_t GetWidth();
	int32_t GetHeight();
};

