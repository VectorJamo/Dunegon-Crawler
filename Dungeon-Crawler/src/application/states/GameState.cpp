#include "GameState.h"
#include <iostream>

#include "../tilemap/MapConstants.h"


GameState::GameState(Window* window)
	:StateManager(window)
{
	LoadAssets();
    
	m_Player = new Dwarf({ 200.0f, 200.0f }, { 64.0f, 64.0f }, &m_Assets->GetTexture(m_Assets->GetFromImageDir("Players/Dwarf/dwarf x1.png")),
		{ 0, 0, 32, 32 }, "Dwarf");

	m_UILayer = new UILayer();

	m_Dialogue = new Dialogue("Hello, Dialogue!", m_Assets);
}

GameState::~GameState()
{
	delete m_Assets;
	delete m_Player;
	delete m_UILayer;
}


void GameState::LoadAssets()
{
	m_Assets = new AssetManager();
	m_Assets->LoadTexture(m_Assets->GetFromImageDir("Players/Dwarf/dwarf x1.png"));
	m_Assets->LoadFont(m_Assets->GetFromFontDir("8-bit/8-bit-pusab.ttf"));
}

void GameState::InitEntities()
{
}

void GameState::InitObjects()
{
}

void GameState::InitUI()
{
}

void GameState::Update(float deltaTime)
{
	m_Player->Update(deltaTime);
	m_Dialogue->Update(deltaTime);
}

void GameState::Render()
{
	m_Player->Render(0.0f, 0.0f, GetWindow(), false);
	m_UILayer->Render(GetWindow(), m_Player->GetHealth());
	m_Dialogue->Render(GetWindow());
}
