#include "Game.h"
#include <iostream>

Game::Game(Window* window)
	:m_ApplicationWindow(window)
{
	StateManager::CurrentState = new MenuState(window);
}

Game::~Game()
{
	delete StateManager::CurrentState;
}

void Game::Update(float deltaTime)
{
	StateManager::CurrentState->Update(deltaTime);
}

void Game::Render()
{
	StateManager::CurrentState->Render();
}
