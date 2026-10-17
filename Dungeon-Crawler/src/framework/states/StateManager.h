#pragma once

#include "../graphics/Window.h"

class StateManager
{
private:
	Window* m_Window;

public:
	static StateManager* CurrentState;

	StateManager(Window* window);
    virtual ~StateManager() = 0;

	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

	inline Window* GetWindow() { return m_Window; }
};
