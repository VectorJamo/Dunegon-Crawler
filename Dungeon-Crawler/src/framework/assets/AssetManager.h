#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

class AssetManager
{
private:
	// Texture path to sf::texture map
	std::unordered_map<std::string, sf::Texture> m_Textures;

	// Font path to sf::Font map
	std::unordered_map<std::string, sf::Font> m_Fonts;

	// Shader path to sf::Shader map
	std::unordered_map<std::string, sf::Shader> m_Shaders;

private:
	bool HasTexture(const std::string& path);
	bool HasFont(const std::string& path);
	bool HasShader(const std::string& path);

public:
	~AssetManager();

	// Textures
	void LoadTexture(const std::string& path);
	sf::Texture& GetTexture(const std::string& path);
	sf::Texture& GetTextureByName(const std::string& name);

	// Fonts
	void LoadFont(const std::string& path);
	sf::Font& GetFont(const std::string& path);
	sf::Font& GetFontByName(const std::string& name);

	// Shaders
	void LoadShader(const std::string& path, sf::Shader::Type shaderType);
	sf::Shader& GetShader(const std::string& path);
	sf::Shader& GetShaderByName(const std::string& name);

	static std::string GetFromImageDir(const std::string& imageName);
	static std::string GetFromFontDir(const std::string& fontName);
	static std::string GetFromShaderDir(const std::string& shaderName);
};

