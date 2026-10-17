#include "StateManager.h"

StateManager* StateManager::CurrentState = nullptr;

StateManager::StateManager(Window* window)
	:m_Window(window)
{
	
}

StateManager::~StateManager()
{
    
}
