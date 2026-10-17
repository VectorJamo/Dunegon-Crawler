#pragma once

#include <iostream>
#include <memory>

// Engine
#include "framework/assets/AssetManager.h"
#include "framework/states/StateManager.h"
#include "framework/tilemap/TileMap.h"
#include "framework/input/Input.h"

// Game
#include "application/entities/Dwarf.h"
#include "application/layers/UILayer.h"
#include "application/systems/Dialogue.h"

class GameState : public StateManager
{
private:
	// Asset Manager
	AssetManager* m_Assets;

	// Entities
	Dwarf* m_Player;

	// UI
	UILayer* m_UILayer;
	
	// Systems
	Dialogue* m_Dialogue;
    	
private:
	void LoadAssets();

	void InitEntities();
	void InitObjects();
	void InitUI();

public:
	GameState(Window* window);
	~GameState();

	void Update(float deltaTime) override;
	void Render() override;
};

