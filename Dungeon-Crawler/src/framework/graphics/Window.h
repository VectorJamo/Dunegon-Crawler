#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Window
{
private:
	sf::RenderWindow* m_Window;

public:
	Window(uint32_t width, uint32_t height, const std::string& title);
	~Window();

	void Clear();
	void Update();
	void Show();

	void Draw(sf::Sprite* sprite);

	bool IsOpen();
	void Close();

	void EnableVsync();

	inline sf::RenderWindow* GetWindowInstance() { return m_Window; }
};

