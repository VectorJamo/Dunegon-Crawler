#include "Button.h"

#include "framework/input/Input.h"

Button::Button(const std::string& text, sf::Font& font)
{
	m_PaddingX = 0;
	m_PaddingY = 0;
	m_IsHovered = false;
	m_IsClicked = false;

	m_Text = new Text(font, text);

	m_Button.setOutlineThickness(2);
	m_Button.setOutlineColor(sf::Color(255, 255, 255, 255));
	m_Button.setFillColor(sf::Color::Transparent);

	m_Button.setSize({ (float)m_Text->GetWidth(), (float)m_Text->GetHeight() });
}

Button::~Button()
{
}

void Button::Update(float deltaTime)
{
	m_IsHovered = false;
	m_IsClicked = false;

	sf::Vector2i mPos = Input::GetMousePosition();

	if (mPos.x > m_Button.getPosition().x && mPos.x < m_Button.getPosition().x + m_Button.getSize().x
		&& mPos.y > m_Button.getPosition().y && mPos.y < m_Button.getPosition().y + m_Button.getSize().y)
	{
		m_IsHovered = true;

		if (Input::IsMouseButtonPressed(MouseButton::Left))
		{
			m_IsClicked = true;
		}
	}
}

void Button::Render(Window* window)
{
	// Button
	window->GetWindowInstance()->draw(m_Button);

	// Text
	m_Text->Render(window);
}

void Button::SetPosition(const sf::Vector2f& position)
{
	m_Button.setPosition(position);
	RecalculateTextPosition();
}

void Button::SetCharacterSize(int32_t size)
{
	m_Text->SetCharacterSize(size);
	RecalculateButtonSize();
}

void Button::SetOutlineColor(sf::Color color)
{
	m_Button.setOutlineColor(color);
}

void Button::SetBackgroundColor(sf::Color color)
{
	m_Button.setFillColor(color);
}

void Button::SetTextColor(sf::Color color)
{
	m_Text->SetFillColor(color);
}

void Button::SetPadding(int32_t paddingX, int32_t paddingY)
{
	m_PaddingX = paddingX;
	m_PaddingY = paddingY;
	RecalculateButtonSize();
}

void Button::RecalculateButtonSize()
{
	float buttonWidth = m_Text->GetWidth() + m_PaddingX*2;
	float buttonHeight = m_Text->GetHeight() + m_PaddingY*2;

	m_Button.setSize({ buttonWidth, buttonHeight });

	RecalculateTextPosition();
}

void Button::RecalculateTextPosition()
{
	float textPositionX = m_Button.getPosition().x + m_PaddingX;
	float textPositionY = m_Button.getPosition().y + m_PaddingY;
	
	m_Text->SetPosition({ textPositionX, textPositionY });
}

int32_t Button::GetWidth() const
{
	return m_Button.getSize().x;
}

int32_t Button::GetHeight() const
{
	return m_Button.getSize().y;
}