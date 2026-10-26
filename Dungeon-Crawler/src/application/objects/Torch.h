#pragma once
#include "framework/objects/Object.h"

class Torch: public Object
{
private:

public:
	Torch(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, Rect textureArea);
	~Torch();

	void Update(float deltaTime);
};

