#include "TileManager.h"

TileManager::TileManager()
{
}

TileManager::~TileManager()
{
}

void TileManager::AddTile(const std::string& tileName, sf::Texture& texture, Rect textureRect)
{
	Tile* tile = new Tile(tileName, texture, textureRect);

	m_GameTiles[tileName] = tile;
}

Tile* TileManager::GetTileByName(const std::string& tileName)
{
	return m_GameTiles[tileName];
}
