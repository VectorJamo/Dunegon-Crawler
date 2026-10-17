#pragma once

#include "framework/utils/TextureArea.h"
#include "application/tilemap/MapConstants.h"

struct Tile
{
	std::string tileName;
	TextureArea textureArea;
	bool isCollideable = true;
	Rect collisionRect = { 0, 0, MapConstants::TileSize, MapConstants::TileSize };

	Tile(const std::string& tileName, sf::Texture& texture, const Rect& textureRect);
	Tile(const std::string& tileName, sf::Texture& texture, const Rect& textureRect, bool isCollideable, const Rect& collisionRect);
};

