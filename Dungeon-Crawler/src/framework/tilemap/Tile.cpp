#include "Tile.h"

Tile::Tile(const std::string& tileName, sf::Texture& texture, const Rect& textureRect)
{
	this->tileName = tileName;
	
	textureArea.texture = &texture;
	textureArea.textureRect = textureRect;
}

Tile::Tile(const std::string& tileName, sf::Texture& texture, const Rect& textureRect, bool isCollideable, const Rect& collisionRect)
{
	this->tileName = tileName;
	
	textureArea.texture = &texture;
	textureArea.textureRect = textureRect;

	this->isCollideable = isCollideable;
	this->collisionRect = collisionRect;
}