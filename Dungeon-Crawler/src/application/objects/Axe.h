#pragma once
#include "framework/objects/Object.h"
#include "framework/assets/AssetManager.h"

class Axe : public Object
{
private:

public:
	Axe(sf::Vector2f worldPosition, sf::Vector2f size, AssetManager* assets);
};

