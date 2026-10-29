#include "InventoryItem.h"

#include "application/tilemap/MapConstants.h"

#include "Inventory.h"

InventoryItem::InventoryItem(const std::string& itemName, int32_t itemCount, const std::string& itemDescription, Sprite* iconSprite, sf::Font& font)
	:itemName(itemName), itemCount(itemCount), itemDescripition(itemDescription), itemIconSprite(iconSprite)
{
	itemNameText = new Text(font, itemName);
	itemNameText->SetCharacterSize(MapConstants::TileSize / 2.5f);
	itemNameText->SetFillColor({ 100, 150, 225, 255 });
	itemNameText->SetPosition(Inventory::InventoryPosition + Inventory::InventoryDescAreaOffset + sf::Vector2f(2.0f, 2.0f));

	itemDescriptionText = new Text(font, itemDescription);
	itemDescriptionText->SetCharacterSize(MapConstants::TileSize / 2.5f);
	itemDescriptionText->SetPosition(itemNameText->GetPosition() + sf::Vector2f(0.0f, (float)itemNameText->GetHeight()*3));

	itemCountText = new Text(font, std::to_string(itemCount));
	itemCountText->SetCharacterSize(MapConstants::TileSize / 4.0f);

	std::string itemDesc = itemDescription;
	if (itemDescriptionText->GetWidth() > Inventory::InventoryDimension.x)
	{
		std::cout << itemDescriptionText->GetWidth() << std::endl;

		int32_t factor = itemDescriptionText->GetWidth() / Inventory::InventoryDimension.x; // How many times we need to split the string
		int32_t location = itemDesc.length() / (factor + 1); // In what intervals should we split the string

		for (int i = 1; i <= factor; i++)
		{
			int32_t loc = location * i;
			itemDesc.insert(loc, 1, '\n');
		}
	}

	itemDescriptionText->SetString(itemDesc);
}

InventoryItem::~InventoryItem()
{
}