#include "TextureArea.h"

TextureArea::TextureArea()
	:texture(nullptr)
{
}

TextureArea::TextureArea(sf::Texture* texture, const Rect& rect)
	:texture(texture), textureRect(rect)
{
}
