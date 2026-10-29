#include "TimedText.h"

#include "application/tilemap/MapConstants.h"

TimedText::TimedText(sf::Vector2f position, const std::string& text, sf::Font& font, sf::Color color, int charSize, float timeToLiveInSeconds)
{
	m_Text = new Text(font, text);
	m_Text->SetCharacterSize(charSize);
	m_Text->SetFillColor(color);
	m_Text->SetPosition(position);

	m_Timer = 0.0f;
	m_HasRanOutOfTime = false;
}

TimedText::TimedText(sf::Vector2f position, const std::string& text, sf::Font& font, float timeToLiveInSeconds)
{
	m_Text = new Text(font, text);
	m_Text->SetCharacterSize(MapConstants::TileSize/3.0f);
	m_Text->SetPosition(position);
}

TimedText::~TimedText()
{
	delete m_Text;
}

void TimedText::Update(float deltaTime)
{
	m_Timer += deltaTime;
	if (m_Timer > m_TTL && !m_HasRanOutOfTime)
		m_HasRanOutOfTime = true;
}

void TimedText::Render(Window* window)
{
	m_Text->Render(window);
}
