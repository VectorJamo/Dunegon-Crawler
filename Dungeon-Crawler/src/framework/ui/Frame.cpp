#include "Frame.h"

Frame::Frame(const sf::Vector2f& position, const sf::Vector2f& dimension, int32_t defaultMargin)
	:m_Position(position), m_Dimension(dimension), m_CurrentY(0), m_DefaultMargin(defaultMargin)
{
}

Frame::~Frame()
{
}

void Frame::PushText(std::unique_ptr<Text>* text, Alignment align)
{
	float textWidth = (*text)->GetWidth();
	float textHeight = (*text)->GetHeight();

	float frameXPos = m_Position.x;
	float frameYPos = m_Position.y;
	float frameWidth = m_Dimension.x;
	float frameHeight = m_Dimension.y;

	switch (align)
	{
	case Alignment::LEFT:
	{
		(*text)->SetPosition({ frameXPos, frameYPos + (float)m_CurrentY });
		break;
	}
	case Alignment::CENTER:
	{
		float frameCenterX = frameXPos + (frameXPos + frameWidth) / 2;
		float xPos = frameCenterX - (*text)->GetWidth()/2;

		(*text)->SetPosition({ xPos, (float)m_CurrentY });
		break;
	}
	case Alignment::RIGHT:
	{
		float frameRightX = frameXPos + frameWidth;
		float xPos = frameRightX - (*text)->GetWidth();

		(*text)->SetPosition({ xPos, (float)m_CurrentY });
		break;
	}
	default:
		break;
	}

	m_CurrentY += (textHeight + m_DefaultMargin);
	m_Texts.push_back(text);
}

void Frame::PushButton(std::unique_ptr<Button>* button, Alignment align)
{
	float buttonWidth = (*button)->GetWidth();
	float buttonHeight = (*button)->GetHeight();

	float frameXPos = m_Position.x;
	float frameYPos = m_Position.y;
	float frameWidth = m_Dimension.x;
	float frameHeight = m_Dimension.y;

	switch (align)
	{
	case Alignment::LEFT:
	{
		(*button)->SetPosition({ frameXPos, frameYPos + (float)m_CurrentY });
		break;
	}
	case Alignment::CENTER:
	{
		float frameCenterX = frameXPos + (frameXPos + frameWidth) / 2;
		float xPos = frameCenterX - (*button)->GetWidth() / 2;

		(*button)->SetPosition({ xPos, (float)m_CurrentY });
		break;
	}
	case Alignment::RIGHT:
	{
		float frameRightX = frameXPos + frameWidth;
		float xPos = frameRightX - (*button)->GetWidth();

		(*button)->SetPosition({ xPos, (float)m_CurrentY });
		break;
	}
	default:
		break;
	}

	m_CurrentY += (buttonHeight + m_DefaultMargin);
	m_Buttons.push_back(button);
}

void Frame::PushGap(int32_t gap)
{
	m_CurrentY += gap;
}

void Frame::Render(Window* window)
{
	for (auto& text : m_Texts)
		(*text)->Render(window);
	for (auto& button : m_Buttons)
		(*button)->Render(window);
}
