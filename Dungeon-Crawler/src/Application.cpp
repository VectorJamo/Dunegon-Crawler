#include "Application.h"
#include <iostream>

Application::Application(uint32_t width, uint32_t height, const std::string& title)
{
	m_Window = new Window(width, height, title);
	m_Window->EnableVsync();
	
	Input::SetActiveWindow(m_Window);

	m_Game = new Game(m_Window);
}

Application::~Application()
{
	delete m_Window;
	delete m_Game;
}

Application* Application::CreateApplication(uint32_t width, uint32_t height, const std::string& title)
{
	return new Application(width, height, title);
}

void Application::Run()
{
	while (m_Window->IsOpen()) 
	{
		float deltaTime = m_Clock.restart().asSeconds();

		while (auto event = m_Window->GetWindowInstance()->pollEvent())
		{
			if (event->is<sf::Event::Closed>()) 
			{
				m_Window->Close();
			}
		}

		// Clear the frame
		m_Window->Clear();

		// Game logic 
		m_Game->Update(deltaTime);

		// Rendering
		m_Game->Render();

		// Swap buffers
		m_Window->Show();
	}
}
