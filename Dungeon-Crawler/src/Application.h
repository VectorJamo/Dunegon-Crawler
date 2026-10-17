#pragma once
#include "framework/graphics/Window.h"
#include "framework/game/Game.h"
#include "framework/input/Input.h"

class Application
{
private:
	Window* m_Window;
	Game* m_Game;

	sf::Clock m_Clock;

	Application(uint32_t width, uint32_t height, const std::string& title);

public:
	~Application();

	void Run();

	static Application* CreateApplication(uint32_t width, uint32_t height, const std::string& title);
};

