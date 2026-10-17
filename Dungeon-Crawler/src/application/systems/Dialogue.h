#pragma once
#include <string>
#include "framework/graphics/Window.h"
#include "application/tilemap/MapConstants.h"
#include "framework/ui/Text.h"
#include "framework/assets/AssetManager.h"

class Dialogue
{
private:
	static constexpr int32_t DialogueCharacterSize = MapConstants::TileSize / 3;
	static constexpr int32_t DialogueBoxWidth = MapConstants::ScreenWidth * 0.90f;
	static constexpr int32_t DialogueBoxHeight = MapConstants::ScreenHeight / 4.0f;
	static constexpr sf::Vector2f DialogueBoxOffset = { MapConstants::ScreenWidth * 0.05f, MapConstants::ScreenHeight * 0.1f };
	static constexpr float DialogueSpeed = 0.05f; // Displays a character every 0.05 second

	static constexpr sf::Color DialogueBoxColor = { 40, 40, 40, 100 };

	float m_Timer;

	// Dialogue Text
	std::string m_Dialogue;
	Text* m_Text;
	
	int32_t m_CurrentChar;
	
	// Dialgoue Box
	sf::RectangleShape m_DialogueBox;

	bool m_HasFinishedDialogue;

public:
	Dialogue(const std::string& dialogue, AssetManager* assetManager);
	~Dialogue();

	void Update(float deltaTime);
	void Render(Window* window);

	inline bool HasFinishedDialogue() { return m_HasFinishedDialogue; }
};

