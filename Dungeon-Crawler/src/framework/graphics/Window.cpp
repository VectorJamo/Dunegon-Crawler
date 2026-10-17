#include "Window.h"

Window::Window(uint32_t width, uint32_t height, const std::string& title)
{
	m_Window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(width, height)), title);
	m_Window->setMinimumSize(sf::Vector2u(width, height));
	m_Window->setMaximumSize(sf::Vector2u(width, height));
}

Window::~Window()
{
	delete m_Window;
}

void Window::Clear()
{
	m_Window->clear();
}

void Window::Update()
{

}

void Window::Show()
{
	m_Window->display();
}

void Window::Draw(sf::Sprite* sprite)
{
	m_Window->draw(*sprite);
}

bool Window::IsOpen()
{
	return m_Window->isOpen();
}

void Window::Close()
{
	m_Window->close();
}

void Window::EnableVsync()
{
	m_Window->setVerticalSyncEnabled(true);
}
