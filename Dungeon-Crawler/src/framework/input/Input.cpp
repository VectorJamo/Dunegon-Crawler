#include "Input.h"

Window* Input::m_Window = nullptr;

void Input::SetActiveWindow(Window*& window)
{
    m_Window = window;
}

bool Input::IsKeyPressed(const Key& key)
{
    return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

bool Input::IsMouseButtonPressed(const MouseButton& button)
{
    return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
}

sf::Vector2i Input::GetMousePosition()
{
    return sf::Mouse::getPosition(*m_Window->GetWindowInstance());
}
