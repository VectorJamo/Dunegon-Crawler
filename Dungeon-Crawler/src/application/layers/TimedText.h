#pragma once
#include "framework/ui/Text.h"

// A short lived text for n seconds
class TimedText
{
private:
	Text* m_Text;
	float m_TTL; // TTL-> Time To Live (In seconds)

	float m_Timer;
	bool m_HasRanOutOfTime;

public:
	TimedText(sf::Vector2f position, const std::string& text, sf::Font& font, sf::Color color, int charSize, float timeToLiveInSeconds);
	TimedText(sf::Vector2f position, const std::string& text, sf::Font& font, float timeToLiveInSeconds);
	~TimedText();

	void Update(float deltaTime);
	void Render(Window* window);

	inline bool HasRanOutOfTime() const { return  m_HasRanOutOfTime; }
};

