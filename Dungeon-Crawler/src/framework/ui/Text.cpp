#include "Text.h"

Text::Text(sf::Font& font)
	:m_Text(nullptr), m_Font(font), m_String(""), m_Position(0.0f, 0.0f)
{
	m_Text = new sf::Text(font);

	m_Text->setString(m_String);
	m_Text->setPosition(m_Position);
}

Text::Text(sf::Font& font, const std::string& string)
	:m_Text(nullptr), m_Font(font), m_String(string), m_Position(0.0f, 0.0f)
{
	m_Text = new sf::Text(font);

	m_Text->setString(m_String);
	m_Text->setPosition(m_Position);
}

Text::Text(sf::Font& font, const std::string& string, const sf::Vector2f& position)
	:m_Text(nullptr), m_Font(font), m_String(string), m_Position(position)
{
	m_Text = new sf::Text(font);

	m_Text->setString(m_String);
	m_Text->setPosition(m_Position);
}

Text::~Text()
{
	delete m_Text;
}

void Text::SetPosition(sf::Vector2f position)
{
	m_Position = position;
	m_Text->setPosition(position);
}

void Text::SetString(const std::string& string)
{
	m_Text->setString(string);

	m_String = string;
}

void Text::SetCharacterSize(int32_t sizeInPixels)
{
	m_Text->setCharacterSize(sizeInPixels);
}

void Text::SetFillColor(sf::Color color)
{
	m_Text->setFillColor(color);
}

void Text::SetTextStyle(sf::Text::Style style)
{
	m_Text->setStyle(style);
}

void Text::Render(Window* window)
{
	window->GetWindowInstance()->draw(*m_Text);
}

int32_t Text::GetWidth()
{
	return (int32_t)(m_Text->getLocalBounds().size.x);
}

int32_t Text::GetHeight()
{
	return (int32_t)(m_Text->getLocalBounds().size.y);
}
