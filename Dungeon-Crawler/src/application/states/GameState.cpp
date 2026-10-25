#include "GameState.h"
#include <iostream>

#include "../tilemap/MapConstants.h"


GameState::GameState(Window* window)
	:StateManager(window)
{
	LoadAssets();

	InitMap();
	InitEntities();
    
	m_UILayer = new UILayer();

	m_DialogueSystem = new DialogueSystem(m_Assets);

	m_DialogueSystem->PushDialogueIntoQueue(new Dialogue("Hello, Dialogue!", m_Assets));
	//m_DialogueSystem->PushDialogueIntoQueue(new Dialogue("This is another one. This one will check for string wrapping!", m_Assets));
	m_DialogueSystem->PlayCurrentDialogueQueue();

	m_Camera = new Camera(m_Player->GetWorldPosition(), {MapConstants::ScreenWidth, MapConstants::ScreenHeight});
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
	m_Tiles->AddTile("Window1Tile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(416, 0, 16, 16));
	m_Tiles->AddTile("Window2Tile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(432, 0, 16, 16));
	m_Tiles->AddTile("Vent1Tile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(384, 0, 16, 16));
	m_Tiles->AddTile("Painting1Tile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(448, 0, 16, 16));
	m_Tiles->AddTile("Painting2Tile", m_Assets->GetTextureByName("Tileset/tileset.png"), Rect(464, 0, 16, 16));

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
}

void GameState::InitEntities()
{
	m_Player = new Dwarf({ 200.0f, 200.0f }, { 64.0f, 64.0f }, &m_Assets->GetTexture(m_Assets->GetFromImageDir("Players/Dwarf/dwarf x1.png")),
		{ 0, 0, 32, 32 }, "Dwarf");
}

void GameState::InitObjects()
{
}

void GameState::InitUI()
{
}

void GameState::Update(float deltaTime)
{
	m_Camera->Update(deltaTime, m_Player->GetWorldPosition(), m_Player->GetEntitySprite()->GetSize());
	
	m_DialogueSystem->Update(deltaTime);
	
	if (!m_DialogueSystem->IsCurrentlyPlaying())
	{
		m_Player->Update(deltaTime, m_Camera);
	}

}

void GameState::Render()
{
	m_BaseMapLayer->Render(m_Camera->GetCameraPosition(), m_Camera->GetCameraVisibilityRect());
	m_ObjectsMapLayer->Render(m_Camera->GetCameraPosition(), m_Camera->GetCameraVisibilityRect());

	m_Player->Render(m_Camera->GetCameraPosition(), m_Camera->GetCameraVisibilityRect(), GetWindow(), false);
	m_UILayer->Render(GetWindow(), m_Player->GetHealth());
	m_DialogueSystem->Render(GetWindow());
}
