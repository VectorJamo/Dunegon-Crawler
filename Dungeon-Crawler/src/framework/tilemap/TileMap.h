#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

#include "../utils/TextureArea.h"
#include "../graphics/Window.h"
#include "Tile.h"

class TileMap
{
private:
	Window* m_Window;

	int32_t** m_Map;
	int32_t m_WorldRows, m_WorldCols, m_TileSize;

	// If using 1 tile -> 1 texture
	std::unordered_map<uint16_t, sf::Texture*> m_TileIdentity;

	// If using texture atlases
	std::unordered_map<uint16_t, Tile*> m_TileIdentityForAtlas;

private:
	void LoadMap(const std::string& path);
	void LoadCSVMap(const std::string& path);
	void LogMap();

public:
	TileMap(Window* window, int32_t worldRows, int32_t worldCols, int32_t tileSize, const std::string& mapPath, bool loadFromCSV = false);
	~TileMap();

	// If using 1 tile -> 1 texture
	void SetTileIdentity(uint16_t tileNum, sf::Texture* texture);

	// If using texture atlases
	void SetTileIdentity(uint16_t tileNum, Tile* tile);

	void Render(sf::Vector2f cameraPosition, sf::Vector2f cameraRect);
	void Render(sf::Vector2f cameraPosition, sf::Vector2f cameraRect, sf::Shader* shader);

	int32_t** GetMap() { return m_Map; }
};
