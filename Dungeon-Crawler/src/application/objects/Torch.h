#pragma once
#include "framework/objects/Object.h"
#include "framework/entities/Animation.h"

class Torch: public Object
{
private:
	AnimationComponent* m_Animation;

public:
	Torch(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, Rect textureArea);
	~Torch();

	void Update(float deltaTime);
};

