#pragma once
#include "framework/graphics/Window.h"
#include "framework/graphics/Sprite.h"

#include "framework/ui/Text.h"
#include "framework/assets/AssetManager.h"

class UILayer
{
private:
	AssetManager* m_Assets;

	Text* m_VersionText;

	Sprite* m_HealthFullSprite, *m_HealthEmptySprite;

public:
	UILayer();
	~UILayer();

	void Update(float deltaTime);
	void Render(Window* window, float playerHealth);
};

