#include "TileMap.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

TileMap::TileMap(Window* window, int32_t worldRows, int32_t worldCols, int32_t tileSize, const std::string& mapPath, bool loadFromCSV)
	:m_Window(window), m_WorldRows(worldRows), m_WorldCols(worldCols), m_TileSize(tileSize)
{
	m_Map = new int32_t*[worldRows];
	for (int i = 0; i < worldRows; i++)
	{
		m_Map[i] = new int32_t[worldCols];
	}

	if (loadFromCSV)
		LoadCSVMap(mapPath);
	else
		LoadMap(mapPath);
}

TileMap::~TileMap()
{
	for (int i = 0; i < m_WorldRows; i++) 
	{
		delete[] m_Map[i];
	}
}

void TileMap::SetTileIdentity(uint16_t tileNum, sf::Texture* texture)
{
	m_TileIdentity[tileNum] = texture;
}

void TileMap::SetTileIdentity(uint16_t tileNum, Tile* tile)
{
	m_TileIdentityForAtlas[tileNum] = tile;
}

void TileMap::LoadMap(const std::string& path)
{
	std::fstream file(path);
	if (!file.is_open())
	{
		std::cout << "Cannot read file: " << path << std::endl;
		return;
	}

	std::string line;
	int32_t row = 0;
	while (std::getline(file, line))
	{
		int32_t col = 0;
		for (char& c : line)
		{
			m_Map[row][col] = ((c) - '0');
			col++;
		}
		row++;
	}
}

void TileMap::LoadCSVMap(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << "Cannot read CSV file: " << path << std::endl;
		return;
	}

	std::string line;
	int32_t row = 0;

	while (std::getline(file, line))
	{
		int32_t col = 0;

		std::stringstream ss(line); // Tile Row
		std::string cell; // Tile

		while (std::getline(ss, cell, ','))
		{
			int16_t tileNumber = std::stoi(cell);
			m_Map[row][col] = tileNumber;

			col++;
		}
		row++;
	}
}

void TileMap::LogMap()
{
	for (int i = 0; i < m_WorldRows; i++)
	{
		for (int j = 0; j < m_WorldCols; j++)
		{
			std::cout << (int32_t)m_Map[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}

void TileMap::Render(sf::Vector2f cameraPosition, sf::Vector2f cameraRect)
{
	if (!m_TileIdentity.empty())
	{
		// Render from m_TileIdentity
		for (int i = 0; i < m_WorldRows; i++)
		{
			for (int j = 0; j < m_WorldCols; j++)
			{
				int32_t tileNum = m_Map[i][j];

				if (m_TileIdentity.find(tileNum) != m_TileIdentity.end())
				{
					sf::Texture* tileTexture = m_TileIdentity[tileNum];

					sf::Sprite sprite(*tileTexture);

					float worldPosX = j * (float)m_TileSize;
					float worldPosY = i * (float)m_TileSize;

					float cameraTopLeftX = cameraPosition.x - cameraRect.x / 2;
					float cameraTopLeftY = cameraPosition.y - cameraRect.y / 2;

					float screenPosX = worldPosX - cameraTopLeftX;
					float screenPosY = worldPosY - cameraTopLeftY;

					sf::Vector2u textureSize = tileTexture->getSize();

					sprite.setPosition(sf::Vector2f(screenPosX, screenPosY));
					sprite.setScale(sf::Vector2f((float)m_TileSize / (float)textureSize.x, (float)m_TileSize / (float)textureSize.y));

					m_Window->GetWindowInstance()->draw(sprite);
				}
			}
		}
		return;
	}
	// Render from m_TileIdentityForAtlas
	for (int i = 0; i < m_WorldRows; i++)
	{
		for (int j = 0; j < m_WorldCols; j++)
		{
			int32_t tileNum = m_Map[i][j];

			if (m_TileIdentityForAtlas.find(tileNum) != m_TileIdentityForAtlas.end())
			{
				TextureArea textureArea = m_TileIdentityForAtlas[tileNum]->textureArea;

				sf::Texture* texture = textureArea.texture;
				Rect textureRect = textureArea.textureRect;

				sf::Sprite sprite(*texture);

				sf::IntRect srcRect(sf::Vector2i(textureRect.x, textureRect.y), sf::Vector2i(textureRect.width, textureRect.height));
				sprite.setTextureRect(srcRect);

				float worldPosX = j * (float)m_TileSize;
				float worldPosY = i * (float)m_TileSize;

				float cameraTopLeftX = cameraPosition.x - cameraRect.x / 2;
				float cameraTopLeftY = cameraPosition.y - cameraRect.y / 2;

				float screenPosX = worldPosX - cameraTopLeftX;
				float screenPosY = worldPosY - cameraTopLeftY;

				sprite.setPosition(sf::Vector2f(screenPosX, screenPosY));
				sprite.setScale(sf::Vector2f((float)m_TileSize / (float)textureRect.width, (float)m_TileSize / (float)textureRect.height));

				m_Window->GetWindowInstance()->draw(sprite);
			}
		}
	}
}

void TileMap::Render(sf::Vector2f cameraPosition, sf::Vector2f cameraRect, sf::Shader* shader)
{
	if (!m_TileIdentity.empty())
	{
		// Render from m_TileIdentity
		for (int i = 0; i < m_WorldRows; i++)
		{
			for (int j = 0; j < m_WorldCols; j++)
			{
				int32_t tileNum = m_Map[i][j];

				if (m_TileIdentity.find(tileNum) != m_TileIdentity.end())
				{
					sf::Texture* tileTexture = m_TileIdentity[tileNum];

					sf::Sprite sprite(*tileTexture);

					float worldPosX = j * (float)m_TileSize;
					float worldPosY = i * (float)m_TileSize;

					float cameraTopLeftX = cameraPosition.x - cameraRect.x / 2;
					float cameraTopLeftY = cameraPosition.y - cameraRect.y / 2;

					float screenPosX = worldPosX - cameraTopLeftX;
					float screenPosY = worldPosY - cameraTopLeftY;

					sf::Vector2u textureSize = tileTexture->getSize();

					sprite.setPosition(sf::Vector2f(screenPosX, screenPosY));
					sprite.setScale(sf::Vector2f((float)m_TileSize / (float)textureSize.x, (float)m_TileSize / (float)textureSize.y));

					m_Window->GetWindowInstance()->draw(sprite, shader);
				}
			}
		}
		return;
	}
	// Render from m_TileIdentityForAtlas
	for (int i = 0; i < m_WorldRows; i++)
	{
		for (int j = 0; j < m_WorldCols; j++)
		{
			int32_t tileNum = m_Map[i][j];

			if (m_TileIdentityForAtlas.find(tileNum) != m_TileIdentityForAtlas.end())
			{
				TextureArea textureArea = m_TileIdentityForAtlas[tileNum]->textureArea;

				sf::Texture* texture = textureArea.texture;
				Rect textureRect = textureArea.textureRect;

				sf::Sprite sprite(*texture);

				sf::IntRect srcRect(sf::Vector2i(textureRect.x, textureRect.y), sf::Vector2i(textureRect.width, textureRect.height));
				sprite.setTextureRect(srcRect);

				float worldPosX = j * (float)m_TileSize;
				float worldPosY = i * (float)m_TileSize;

				float cameraTopLeftX = cameraPosition.x - cameraRect.x / 2;
				float cameraTopLeftY = cameraPosition.y - cameraRect.y / 2;

				float screenPosX = worldPosX - cameraTopLeftX;
				float screenPosY = worldPosY - cameraTopLeftY;

				sprite.setPosition(sf::Vector2f(screenPosX, screenPosY));
				sprite.setScale(sf::Vector2f((float)m_TileSize / (float)textureRect.width, (float)m_TileSize / (float)textureRect.height));

				m_Window->GetWindowInstance()->draw(sprite, shader);
			}
		}
	}

}

Tile* TileMap::GetTileFromNumber(int32_t tileNum)
{
	return m_TileIdentityForAtlas[tileNum];
}
