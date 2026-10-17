#include "TileMap.h"
#include <fstream>
#include <string>
#include <iostream>

TileMap::TileMap(Window* window, int32_t worldRows, int32_t worldCols, int32_t tileSize, const std::string& mapPath)
	:m_Window(window), m_WorldRows(worldRows), m_WorldCols(worldCols), m_TileSize(tileSize)
{
	m_Map = new int32_t*[worldRows];
	for (int i = 0; i < worldRows; i++)
	{
		m_Map[i] = new int32_t[worldCols];
	}

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

void TileMap::LogMap()
{
	for (int i = 0; i < m_WorldRows; i++)
	{
		for (int j = 0; j < m_WorldCols; j++)
		{
			std::cout << (int32_t)m_Map[i][j];
		}
		std::cout << std::endl;
	}
}

void TileMap::Render()
{
	if (!m_TileIdentity.empty())
	{
		// Render from m_TileIdentity
		for (int i = 0; i < m_WorldRows; i++)
		{
			for (int j = 0; j < m_WorldCols; j++)
			{
				uint8_t tileNum = m_Map[i][j];

				if (m_TileIdentity.find(tileNum) != m_TileIdentity.end()) 
				{
					sf::Texture* tileTexture = m_TileIdentity[tileNum];
				
					sf::Sprite sprite(*tileTexture);

					float x = j * m_TileSize;
					float y = i * m_TileSize;

					sf::Vector2u textureSize = tileTexture->getSize();

					sprite.setPosition(sf::Vector2f(x, y));
					sprite.setScale(sf::Vector2f((float)m_TileSize/(float)textureSize.x, (float)m_TileSize/(float)textureSize.y));

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
			uint8_t tileNum = m_Map[i][j];

			if (m_TileIdentityForAtlas.find(tileNum) != m_TileIdentityForAtlas.end())
			{
				TextureArea textureArea = m_TileIdentityForAtlas[tileNum]->textureArea;
				
				sf::Texture* texture = textureArea.texture;
				Rect textureRect = textureArea.textureRect;

				sf::Sprite sprite(*texture);

				sf::IntRect srcRect(sf::Vector2i(textureRect.x, textureRect.y), sf::Vector2i(textureRect.width, textureRect.height));
				sprite.setTextureRect(srcRect);

				float x = j * m_TileSize;
				float y = i * m_TileSize;

				sprite.setPosition(sf::Vector2f(x, y));
				sprite.setScale(sf::Vector2f((float)m_TileSize / (float)textureRect.width, (float)m_TileSize / (float)textureRect.height));
				
				m_Window->GetWindowInstance()->draw(sprite);
			}
		}
	}

}

void TileMap::Render(sf::Shader* shader)
{
	if (!m_TileIdentity.empty())
	{
		// Render from m_TileIdentity
		for (int i = 0; i < m_WorldRows; i++)
		{
			for (int j = 0; j < m_WorldCols; j++)
			{
				uint8_t tileNum = m_Map[i][j];

				if (m_TileIdentity.find(tileNum) != m_TileIdentity.end())
				{
					sf::Texture* tileTexture = m_TileIdentity[tileNum];

					sf::Sprite sprite(*tileTexture);

					float x = j * m_TileSize;
					float y = i * m_TileSize;

					sf::Vector2u textureSize = tileTexture->getSize();

					sprite.setPosition(sf::Vector2f(x, y));
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
			uint8_t tileNum = m_Map[i][j];

			if (m_TileIdentityForAtlas.find(tileNum) != m_TileIdentityForAtlas.end())
			{
				TextureArea textureArea = m_TileIdentityForAtlas[tileNum]->textureArea;
				
				Rect textureRect = textureArea.textureRect;

				sf::Sprite sprite(*textureArea.texture);

				sf::IntRect srcRect(sf::Vector2i(textureRect.x, textureRect.y), sf::Vector2i(textureRect.width, textureRect.height));
				sprite.setTextureRect(srcRect);

				float x = j * m_TileSize;
				float y = i * m_TileSize;

				sprite.setPosition(sf::Vector2f(x, y));
				sprite.setScale(sf::Vector2f((float)m_TileSize / (float)textureRect.width, (float)m_TileSize / (float)textureRect.height));

				m_Window->GetWindowInstance()->draw(sprite, shader);
			}
		}
	}
}