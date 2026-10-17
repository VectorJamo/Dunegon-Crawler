#include "AssetManager.h"
#include <iostream>
#include <string>

bool AssetManager::HasTexture(const std::string& path)
{
	return m_Textures.find(path) != m_Textures.end();
}

bool AssetManager::HasFont(const std::string& path)
{
	return m_Fonts.find(path) != m_Fonts.end();
}

bool AssetManager::HasShader(const std::string& path)
{
	return m_Shaders.find(path) != m_Shaders.end();
}

AssetManager::~AssetManager()
{
	m_Textures.clear();
	m_Fonts.clear();
	m_Shaders.clear();
}

void AssetManager::LoadTexture(const std::string& path)
{
	if (!HasTexture(path))
	{
		sf::Texture texture;
		if (!texture.loadFromFile(path))
		{
			std::cout << "Failed to load texture." << std::endl;
			std::cout << "Texture path: " << path << std::endl;
			return;
		}

		m_Textures[path] = std::move(texture);
	}
}

sf::Texture& AssetManager::GetTexture(const std::string& path)
{
    return m_Textures[path];
}

sf::Texture& AssetManager::GetTextureByName(const std::string& name)
{
	std::string path = GetFromImageDir(name);
	return m_Textures[path];
}

void AssetManager::LoadFont(const std::string& path)
{
	if (!HasFont(path))
	{
		sf::Font font;
		if (!font.openFromFile(path))
		{
			std::cout << "Failed to load font." << std::endl;
			std::cout << "Font path: " << path << std::endl;
			return;
		}
		m_Fonts[path] = std::move(font);
	}
}

sf::Font& AssetManager::GetFont(const std::string& path)
{
    return m_Fonts[path];
}

sf::Font& AssetManager::GetFontByName(const std::string& name)
{
	std::string path = GetFromFontDir(name);
	return m_Fonts[path];
}

void AssetManager::LoadShader(const std::string& path, sf::Shader::Type shaderType)
{
	if (!HasShader(path))
	{
		sf::Shader shader;
		if (!shader.loadFromFile(path, shaderType))
		{
			std::cout << "Failed to load shader." << std::endl;
			std::cout << "Shader path: " << path << std::endl;
			return;
		}
		m_Shaders[path] = std::move(shader);
	}
}

sf::Shader& AssetManager::GetShader(const std::string& path)
{
    return m_Shaders[path];
}

sf::Shader& AssetManager::GetShaderByName(const std::string& name)
{
	std::string path = GetFromShaderDir(name);
	return m_Shaders[path];
}

std::string AssetManager::GetFromImageDir(const std::string& imageName)
{
	return std::string("res/images/") + imageName;
}

std::string AssetManager::GetFromFontDir(const std::string& fontName)
{
	return std::string("res/fonts/") + fontName;
}

std::string AssetManager::GetFromShaderDir(const std::string& shaderName)
{
	return std::string("res/shaders/") + shaderName;
}
