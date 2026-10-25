#pragma once

#include <iostream>
#include <memory>

// Engine
#include "framework/assets/AssetManager.h"
#include "framework/states/StateManager.h"
#include "framework/input/Input.h"
#include "framework/tilemap/TileMap.h"
#include "framework/tilemap/TileManager.h"

// Game
#include "application/entities/Dwarf.h"
#include "application/layers/UILayer.h"
#include "application/systems/DialogueSystem.h"
#include "application/systems/Camera.h"

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
	DialogueSystem* m_DialogueSystem;
	Camera* m_Camera;

	// TileMap
	TileManager* m_Tiles;

	TileMap* m_BaseMapLayer, *m_ObjectsMapLayer;

private:
	void LoadAssets();

	void InitMap();
	void InitEntities();
	void InitObjects();
	void InitUI();

public:
	GameState(Window* window);
	~GameState();

	void Update(float deltaTime) override;
	void Render() override;
};

