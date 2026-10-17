#pragma once

#include "Rect.h"
#include <SFML/Graphics.hpp>

struct TextureArea
{
	sf::Texture* texture;
	Rect textureRect;

	TextureArea();
	TextureArea(sf::Texture* texture, const Rect& rect);
};
