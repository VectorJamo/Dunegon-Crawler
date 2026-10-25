#pragma once
#include "Tile.h"
#include <unordered_map>

// Just a place to dump all the tiles
class TileManager
{
private:
	std::unordered_map<std::string, Tile*> m_GameTiles; // Stores a map of tile name to the tile object 

public:
	TileManager();
	~TileManager();

	void AddTile(const std::string& tileName, sf::Texture& texture, Rect& textureRect);

	Tile* GetTileByName(const std::string& tileName);
};

