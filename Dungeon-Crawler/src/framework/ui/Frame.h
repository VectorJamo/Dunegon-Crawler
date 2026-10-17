#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Text.h"
#include "Button.h"

enum class Alignment
{
	LEFT, CENTER, RIGHT
};

class Frame
{
private:
	sf::Vector2f m_Position, m_Dimension;
	int32_t m_CurrentY;
	int32_t m_DefaultMargin;

	std::vector<std::unique_ptr<Text>*> m_Texts;
	std::vector<std::unique_ptr<Button>*> m_Buttons;

public:
	Frame(const sf::Vector2f& position, const sf::Vector2f& dimension, int32_t defaultMargin);
	~Frame();

	void PushText(std::unique_ptr<Text>* text, Alignment align);
	void PushButton(std::unique_ptr<Button>* button, Alignment align);
	void PushGap(int32_t gap);

	void Render(Window* window);
};

