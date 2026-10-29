#pragma once
#include <string>
#include "framework/graphics/Sprite.h"
#include "framework/ui/Text.h"

struct InventoryItem
{
	int32_t itemCount;
	std::string itemName;
	std::string itemDescripition;

	Sprite* itemIconSprite;
	Text* itemNameText, *itemDescriptionText, *itemCountText;
	bool isItemBeingUsed = false;

	InventoryItem(const std::string& itemName, int32_t itemCount, const std::string& itemDescription, Sprite* iconSprite, sf::Font& font);
	~InventoryItem();
};