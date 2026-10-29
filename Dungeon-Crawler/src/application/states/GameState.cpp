#include "GameState.h"
#include <iostream>

#include "../tilemap/MapConstants.h"

GameState::GameState(Window* window)
	:StateManager(window)
{
	LoadAssets();

	InitEntities();
	m_Camera = new Camera(m_Player->GetWorldPosition(), {MapConstants::ScreenWidth, MapConstants::ScreenHeight});
	InitMap();

	InitObjects();
    
	m_UILayer = new UILayer();

	m_DialogueSystem = new DialogueSystem(m_Assets);

	m_DialogueSystem->PushDialogueIntoQueue(new Dialogue("Me: Where am I?", m_Assets)); 
	m_DialogueSystem->PlayCurrentDialogueQueue();

	// Inventory
	m_InventoryManager = new InventoryManager();
	m_InventoryManager->PushItemIntoDatabase("torch", new InventoryItem("torch", 0, "Helps you see things..", new Sprite(&m_Assets->GetTextureByName("Tileset/tileset.png"),
		Inventory::InventoryCellDimension, Rect(368, 32, 16, 16)), m_Assets->GetFontByName("8-bit/8-bit-pusab.ttf")));
	m_InventoryManager->PushItemIntoDatabase("axe", new InventoryItem("axe", 0, "You never know who you'll run into..", new Sprite(&m_Assets->GetTextureByName("Tileset/tileset.png"),
		Inventory::InventoryCellDimension, Rect(320, 32, 16, 16)), m_Assets->GetFontByName("8-bit/8-bit-pusab.ttf")));

	m_Inventory = new Inventory(m_Assets->GetTextureByName("Misc/inventory.png"), m_InventoryManager);
}

GameState::~GameState()
{
	delete m_Assets;
	delete m_Player;
	delete m_UILayer;
	delete m_DialogueSystem;
}

void GameState::LoadAssets()
{
	m_Assets = new AssetManager();
	m_Assets->LoadTexture(m_Assets->GetFromImageDir("Tileset/tileset.png"));
	m_Assets->LoadTexture(m_Assets->GetFromImageDir("Players/Dwarf/dwarf x1.png"));
	m_Assets->LoadTexture(m_Assets->GetFromImageDir("Misc/inventory.png"));

	m_Assets->LoadFont(m_Assets->GetFromFontDir("8-bit/8-bit-pusab.ttf"));
	m_Assets->LoadFont(m_Assets->GetFromFontDir("roboto/Roboto-Regular.ttf"));
}

void GameState::InitMap()
{
	// Load the tiles
	m_Tiles = new TileManager();
	m_Tiles->AddTile("BackgroundTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(32, 0, 16, 16));
	m_Tiles->AddTile("LightFloorTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(32, 16, 16, 16));
	m_Tiles->AddTile("DarkFloorTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(0, 80, 16, 16));
	m_Tiles->GetTileByName("DarkFloorTile")->isCollideable = false;

	m_Tiles->AddTile("Window1Tile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(416, 0, 16, 16));
	m_Tiles->AddTile("Window2Tile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(432, 0, 16, 16));
	m_Tiles->AddTile("Vent1Tile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(384, 0, 16, 16));
	m_Tiles->AddTile("Painting1Tile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(448, 0, 16, 16));
	m_Tiles->AddTile("Painting2Tile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(464, 0, 16, 16));
	m_Tiles->AddTile("RedDoorLockedTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(240, 80, 16, 16));
	m_Tiles->AddTile("WhiteDoorLockedTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(192, 80, 16, 16));
	m_Tiles->AddTile("AxeLeftTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(336, 32, 16, 16));
	m_Tiles->AddTile("AxeRightTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(320, 32, 16, 16));
	m_Tiles->AddTile("BigAxeLeftTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(368, 0, 16, 16));
	m_Tiles->AddTile("BigAxeRightTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(352, 0, 16, 16));
	m_Tiles->AddTile("TargetTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(320, 0, 16, 16));
	m_Tiles->AddTile("DoubleSwordTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(336, 0, 16, 16));
	m_Tiles->AddTile("RedCarpetVerticalTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(176, 160, 16, 16));
	m_Tiles->GetTileByName("RedCarpetVerticalTile")->isCollideable = false;
	m_Tiles->AddTile("RedCarpetBottomTile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(176, 192, 16, 16));
	m_Tiles->GetTileByName("RedCarpetBottomTile")->isCollideable = false;

	// Setup the map
	m_BaseMapLayer = new TileMap(GetWindow(), MapConstants::WorldTileRows, MapConstants::WorldTileCols, MapConstants::TileSize, "res/map/Layer_Base.csv", true);
	m_BaseMapLayer->SetTileIdentity(2, m_Tiles->GetTileByName("BackgroundTile"));
	m_BaseMapLayer->SetTileIdentity(32, m_Tiles->GetTileByName("LightFloorTile"));
	m_BaseMapLayer->SetTileIdentity(150, m_Tiles->GetTileByName("DarkFloorTile"));

	m_ObjectsMapLayer = new TileMap(GetWindow(), MapConstants::WorldTileRows, MapConstants::WorldTileCols, MapConstants::TileSize, "res/map/Layer_Objects.csv", true);
	m_ObjectsMapLayer->SetTileIdentity(24, m_Tiles->GetTileByName("Vent1Tile"));
	m_ObjectsMapLayer->SetTileIdentity(26, m_Tiles->GetTileByName("Window1Tile"));
	m_ObjectsMapLayer->SetTileIdentity(27, m_Tiles->GetTileByName("Window2Tile"));
	m_ObjectsMapLayer->SetTileIdentity(28, m_Tiles->GetTileByName("Painting1Tile"));
	m_ObjectsMapLayer->SetTileIdentity(29, m_Tiles->GetTileByName("Painting2Tile"));
	m_ObjectsMapLayer->SetTileIdentity(165, m_Tiles->GetTileByName("RedDoorLockedTile"));
	m_ObjectsMapLayer->SetTileIdentity(162, m_Tiles->GetTileByName("WhiteDoorLockedTile"));

	m_ObjectsMapLayer->SetTileIdentity(80, m_Tiles->GetTileByName("AxeRightTile"));
	m_ObjectsMapLayer->SetTileIdentity(81, m_Tiles->GetTileByName("AxeLeftTile"));
	m_ObjectsMapLayer->SetTileIdentity(22, m_Tiles->GetTileByName("BigAxeRightTile"));
	m_ObjectsMapLayer->SetTileIdentity(23, m_Tiles->GetTileByName("BigAxeLeftTile"));
	m_ObjectsMapLayer->SetTileIdentity(20, m_Tiles->GetTileByName("TargetTile"));
	m_ObjectsMapLayer->SetTileIdentity(21, m_Tiles->GetTileByName("DoubleSwordTile"));
	m_ObjectsMapLayer->SetTileIdentity(311, m_Tiles->GetTileByName("RedCarpetVerticalTile"));
	m_ObjectsMapLayer->SetTileIdentity(371, m_Tiles->GetTileByName("RedCarpetBottomTile"));

	// Load the shaders
	m_Assets->LoadShader(m_Assets->GetFromShaderDir("fragmentShader.glsl"), sf::Shader::Type::Fragment);
	// Set the texture uniform 
	m_Assets->GetShaderByName("fragmentShader.glsl").setUniform("texture", sf::Shader::CurrentTexture);
}

void GameState::InitEntities()
{
	m_Player = new Dwarf({ 300.0f, 300.0f }, { 64.0f, 64.0f }, &m_Assets->GetTexture(m_Assets->GetFromImageDir("Players/Dwarf/dwarf x1.png")),
		{ 0, 0, 32, 32 }, "Dwarf");
}

void GameState::InitObjects()
{
	m_ObjectsDataMap = new TileMap(GetWindow(), MapConstants::WorldTileRows, MapConstants::WorldTileCols, MapConstants::TileSize, "res/map/Layer_ObjectsData.csv", true);
	std::vector<sf::Vector2f> torchWorldPositions = m_ObjectsDataMap->GetWorldPositionsOfTileNumber(83);

	std::vector<sf::Vector2f> torchScreenPositions;
	for (auto& twp : torchWorldPositions)
		torchScreenPositions.push_back(m_Camera->GetScreenPosFromWorldPos(twp));

	int numTorches = torchScreenPositions.size();
	for (int i = 0; i < numTorches; i++)
	{
		m_Torches.emplace_back(new Torch(torchWorldPositions[i], { 32.0f, 32.0f }, &m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(368, 32, 16, 16)));
	}

	auto location = m_ObjectsDataMap->GetWorldPositionsOfTileNumber(80);
	for (auto& loc : location)
	{
		m_Axe = new Axe(loc, { 32.0f, 32.0f }, m_Assets);
	}
}

void GameState::InitUI()
{
}


void GameState::Update(float deltaTime)
{
	// Update camera
	m_Camera->Update(deltaTime, m_Player->GetWorldPosition(), m_Player->GetEntitySprite()->GetSize());
	
	// Update dialogue sytstem
	m_DialogueSystem->Update(deltaTime);
	
	if (!m_DialogueSystem->IsCurrentlyPlaying())
	{
		m_Player->Update(deltaTime, m_Camera, m_BaseMapLayer, m_ObjectsMapLayer);
	}

	// Update objects
	int32_t size = m_Torches.size();
	sf::Vector2f* torchScreenPositions = (sf::Vector2f*)alloca(sizeof(sf::Vector2f) * size);

	for (int i = 0; i < m_Torches.size(); i++)
	{
		m_Torches[i]->Update(deltaTime);

		sf::Vector2f torchPos = m_Torches[i]->GetObjectSprite()->GetScreenPosition();
		sf::Vector2f torchSize = m_Torches[i]->GetObjectSprite()->GetSize();

		sf::Vector2f torchCenter = torchPos + sf::Vector2f(torchSize.x/2, torchSize.y/2);

		torchScreenPositions[i] = torchCenter;

		// Check for torch-player collision
		if (CollisionHandler::CheckEntityObjectCollision(m_Player, m_Torches[i], deltaTime))
		{
			if (!m_Player->HasTorch())
			{
				// Add the torch to the inventory
				m_Inventory->AddItem("torch");
				m_Player->SetHasTorch(true);

				// Play dialogue
				m_DialogueSystem->PushDialogueIntoQueue(new Dialogue("Me: Got a torch!", m_Assets));
				m_DialogueSystem->PlayCurrentDialogueQueue();

				// Remove the torch
				m_Torches.erase(m_Torches.begin() + i);
			}
		}
	}

	if (m_Axe != nullptr && CollisionHandler::CheckEntityObjectCollision(m_Player, m_Axe, deltaTime))
	{
		if (!m_Player->HasAxe())
		{
			// Add the torch to the inventory
			m_Inventory->AddItem("axe");
			m_Player->SetHasAxe(true);

			// Play dialogue
			m_DialogueSystem->PushDialogueIntoQueue(new Dialogue("Me: Got an axe!", m_Assets));
			m_DialogueSystem->PlayCurrentDialogueQueue();

			delete m_Axe;
			m_Axe = nullptr;
		}
	}
	if (m_Axe != nullptr)
		m_Axe->Update(deltaTime);


	m_Inventory->Update(deltaTime);


	// Update shader uniforms
	sf::Vector2f playerScreenPos = m_Player->GetEntitySprite()->GetScreenPosition();
	Rect playerCollisionBounds = m_Player->GetEntityCollisionRect();

	sf::Vector2f playerCenter = sf::Vector2f(playerScreenPos.x + playerCollisionBounds.x + playerCollisionBounds.width / 2,
		playerScreenPos.y + playerCollisionBounds.y + playerCollisionBounds.height / 2);

	m_Assets->GetShaderByName("fragmentShader.glsl").setUniformArray("torchScreenPositions", torchScreenPositions, size);
	m_Assets->GetShaderByName("fragmentShader.glsl").setUniform("numTorches", size);

	m_Assets->GetShaderByName("fragmentShader.glsl").setUniform("playerCenterScreenPos", playerCenter);
	m_Assets->GetShaderByName("fragmentShader.glsl").setUniform("screenHeight", (float)MapConstants::ScreenHeight);
	m_Assets->GetShaderByName("fragmentShader.glsl").setUniform("playerHasTorch", m_Player->HasTorch());
}

void GameState::Render()
{
	// Render map
	m_BaseMapLayer->Render(m_Camera->GetCameraPosition(), m_Camera->GetCameraVisibilityRect(), &m_Assets->GetShaderByName("fragmentShader.glsl"));
	m_ObjectsMapLayer->Render(m_Camera->GetCameraPosition(), m_Camera->GetCameraVisibilityRect(), &m_Assets->GetShaderByName("fragmentShader.glsl"));

	// Render objects
	for(auto& torch: m_Torches)
		torch->Render(m_Camera->GetCameraPosition(), m_Camera->GetCameraVisibilityRect(), GetWindow(), &m_Assets->GetShaderByName("fragmentShader.glsl"));

	if (m_Axe != nullptr)
		m_Axe->Render(m_Camera->GetCameraPosition(), m_Camera->GetCameraVisibilityRect(), GetWindow(), &m_Assets->GetShaderByName("fragmentShader.glsl"));

	// Render entities
	m_Player->Render(m_Camera->GetCameraPosition(), m_Camera->GetCameraVisibilityRect(), GetWindow(), false, m_Assets->GetShaderByName("fragmentShader.glsl"));
	
	// Render dialogues
	m_DialogueSystem->Render(GetWindow());
	
	// Render UI
	m_UILayer->Render(GetWindow(), m_Player->GetHealth());
	m_Inventory->Render(GetWindow());
}
