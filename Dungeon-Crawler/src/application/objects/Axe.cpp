#include "Axe.h"

Axe::Axe(sf::Vector2f worldPosition, sf::Vector2f size, AssetManager* assets)
	:Object(worldPosition, size, &assets->GetTextureByName("Tileset/tileset.png"), Rect(320, 32, 16, 16))
{
	m_Name = "axe";
}
