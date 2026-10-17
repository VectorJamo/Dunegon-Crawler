#pragma once

#include <SFML/Graphics.hpp>
#include "../graphics/Window.h"

#include "Keys.h"

class Input
{
private:
    static Window* m_Window;

public:
    static void SetActiveWindow(Window*& window);

    static bool IsKeyPressed(const Key& key);
    static bool IsMouseButtonPressed(const MouseButton& button);
    static sf::Vector2i GetMousePosition();
};