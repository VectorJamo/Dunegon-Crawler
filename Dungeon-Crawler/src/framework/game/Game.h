#pragma once
#include "../graphics/Window.h"

#include "../assets/AssetManager.h"

#include "../states/StateManager.h"

#include "application/states/GameState.h"
#include "application/states/MenuState.h"

#include "../input/Input.h"

class Game
{
private:
	Window* m_ApplicationWindow;

public:
	Game(Window* window);
	~Game();

	void Update(float deltaTime);
	void Render();
};

