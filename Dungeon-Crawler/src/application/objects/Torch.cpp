#include "Torch.h"

Torch::Torch(sf::Vector2f worldPosition, sf::Vector2f size, sf::Texture* texture, Rect textureArea)
	:Object(worldPosition, size, texture, textureArea)
{
	m_Animation = new AnimationComponent();
	m_Animation->PushAnimationRect("torchAnimation", Rect(368, 32, 16, 16));
	m_Animation->PushAnimationRect("torchAnimation", Rect(384, 32, 16, 16));
}

Torch::~Torch()
{
	delete m_Animation;
}

void Torch::Update(float deltaTime)
{
	m_Animation->PlayAnimation("torchAnimation");

	SetTextureRect(m_Animation->GetCurrentAnimationRect("torchAnimation"));
}

