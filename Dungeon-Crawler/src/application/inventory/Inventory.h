#pragma once
#include "framework/graphics/Sprite.h"
#include "InventoryItem.h"

#include "InventoryManager.h"

#include "application/tilemap/MapConstants.h"

class Inventory
{
private:
	Sprite* m_InventorySprite;
	InventoryManager* m_InventoryManager;

	std::unordered_map<std::string, InventoryItem*> m_Items; // Stores the current inventory items by it's name.
	std::vector<InventoryItem*> m_ItemsLocationInGrid; // Just for the item's location in the grid

	int32_t m_NumItems;

	bool m_IsInventoryOpen;
	bool m_CanOpenOrCloseInventory;
	float m_InventoryOpenTimer; 

	float m_CellMoveTimer;
	bool m_CanMoveCell;

	sf::Vector2i m_CurrentCell;
	sf::RectangleShape m_InventoryCellOutline;

public:
	// Inventory Dimensions
	static constexpr sf::Vector2f InventoryDimension = { 250.0f, 300.0f };
	static constexpr sf::Vector2f InventoryPosition = { MapConstants::ScreenWidth / 2 - InventoryDimension.x / 2, MapConstants::ScreenHeight / 2 - InventoryDimension.y / 2 };

	static constexpr sf::Vector2f InventoryCellAreaOffset = { 4.0f, 30.0f };
	static constexpr sf::Vector2f InventoryCellDimension = { 30.0f, 30.0f };
	static constexpr sf::Vector2f InventoryCellGap = { 5.0f, 4.0f };

	static constexpr sf::Vector2f InventoryDescAreaOffset = { 5, 135 };

	static constexpr int32_t NumCellsX = 7;
	static constexpr int32_t NumCellsY = 3;

public:
	Inventory(sf::Texture& inventoryTexture, InventoryManager* inventoryManager);
	~Inventory();

	void AddItem(const std::string& itemName);

	void Update(float deltaTime);
	void Render(Window* window);

	sf::Vector2f GetInventoryCellLocation(int32_t cellX, int32_t cellY);
};

