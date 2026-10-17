#include "MenuState.h"
#include <iostream>

#include "application/tilemap/MapConstants.h"
#include "application/states/GameState.h"

MenuState::MenuState(Window* window)
	:StateManager(window)
{
	m_Assets = std::make_unique<AssetManager>();
	LoadAssets();

	// UI
	m_TitleText = std::make_unique<Text>(m_Assets->GetFont(AssetManager::GetFromFontDir("8-bit/8-bit-pusab.ttf")), "Dungeon Crawler");

	m_StartButton = std::make_unique<Button>("Start", m_Assets->GetFont(AssetManager::GetFromFontDir("8-bit/8-bit-pusab.ttf")));
	m_StartButton->SetPadding(20, 10);
	m_QuitButton = std::make_unique<Button>("Quit", m_Assets->GetFont(AssetManager::GetFromFontDir("8-bit/8-bit-pusab.ttf")));
	m_QuitButton->SetPadding(20, 10);

	m_Frame = std::make_unique<Frame>(sf::Vector2f(0, 0), sf::Vector2f(MapConstants::ScreenWidth, MapConstants::ScreenHeight), 20);
	m_Frame->PushGap(100);
	m_Frame->PushText(&m_TitleText, Alignment::CENTER);
	m_Frame->PushGap(50);
	m_Frame->PushButton(&m_StartButton, Alignment::CENTER);
	m_Frame->PushButton(&m_QuitButton, Alignment::CENTER);
}

void MenuState::LoadAssets()
{
	m_Assets->LoadFont(AssetManager::GetFromFontDir("8-bit/8-bit-pusab.ttf"));
}

MenuState::~MenuState()
{
}

void MenuState::Update(float deltaTime)
{
	m_StartButton->Update(deltaTime);
	m_QuitButton->Update(deltaTime);

	if (m_StartButton->IsHovered())
	{
		m_StartButton->SetBackgroundColor({50, 50, 50, 255});
	}
	else {
		m_StartButton->SetBackgroundColor(sf::Color::Transparent);
	}

	if (m_QuitButton->IsHovered())
	{
		m_QuitButton->SetBackgroundColor({ 200, 50, 50, 255 });
	}
	else {
		m_QuitButton->SetBackgroundColor(sf::Color::Transparent);
	}

	if (m_StartButton->IsClicked())
	{
        Window* windowPtr = GetWindow();
		delete CurrentState;

		CurrentState = new GameState(windowPtr);
		return;
	}
	if (m_QuitButton->IsClicked())
	{
		GetWindow()->GetWindowInstance()->close();
		return;
	}
}

void MenuState::Render()
{
	m_Frame->Render(GetWindow());
}
