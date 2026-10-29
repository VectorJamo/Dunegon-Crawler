#include "Inventory.h"

#include "framework/input/Input.h"

Inventory::Inventory(sf::Texture& inventoryTexture, InventoryManager* inventoryManager)
	:m_InventoryManager(inventoryManager)
{
	m_InventorySprite = new Sprite(&inventoryTexture, InventoryDimension);
	m_InventorySprite->SetScreenPosition(InventoryPosition);

	m_IsInventoryOpen = false;
	m_CanOpenOrCloseInventory = true;
	m_InventoryOpenTimer = 0.0f;
	m_CurrentCell = { 0, 0 };
	m_NumItems = 0;

	m_CellMoveTimer = 0.0f;
	m_CanMoveCell = true;
	
	m_InventoryCellOutline.setOutlineThickness(2);
	m_InventoryCellOutline.setOutlineColor({ 255, 255, 255, 255 });
	m_InventoryCellOutline.setFillColor(sf::Color::Transparent);
	m_InventoryCellOutline.setSize(InventoryCellDimension);
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(const std::string& itemName)
{
	// Check if the item already existed in the inventory
	if (m_Items.find(itemName) != m_Items.end())
	{
		// Item already exists. Just increase its count.
		m_Items[itemName]->itemCount++;
		return;
	}

	m_Items[itemName] = m_InventoryManager->GetItemFromName(itemName);
	m_Items[itemName]->itemCount += 1;

	m_Items[itemName]->itemCountText->SetString(std::to_string(m_Items[itemName]->itemCount));

	m_ItemsLocationInGrid.push_back(m_Items[itemName]);

	m_NumItems++;
}

void Inventory::Update(float deltaTime)
{
	if (!m_CanOpenOrCloseInventory)
	{
		m_InventoryOpenTimer += deltaTime;

		if (m_InventoryOpenTimer > 0.5f) // 0.5 second
		{
			m_CanOpenOrCloseInventory = true;
			m_InventoryOpenTimer = 0.0f;
		}
	}

	if (Input::IsKeyPressed(Key::I) && m_CanOpenOrCloseInventory)
	{
		m_CanOpenOrCloseInventory = false;
		m_InventoryOpenTimer = 0.0f;

		m_IsInventoryOpen = !m_IsInventoryOpen;

		std::cout << "Inventory state changed!" << std::endl;
	}

	if (m_IsInventoryOpen && m_CanMoveCell)
	{
		if (Input::IsKeyPressed(Key::Up))
		{
			if (m_CurrentCell.y > 0)
			{
				m_CurrentCell.y--;
				m_CanMoveCell = false;
			}
		}
		if (Input::IsKeyPressed(Key::Left))
		{
			if (m_CurrentCell.x > 0)
			{
				m_CurrentCell.x--;
				m_CanMoveCell = false;
			}
		}
		if (Input::IsKeyPressed(Key::Down))
		{
			if (m_CurrentCell.y < NumCellsY - 1)
			{
				m_CurrentCell.y++;
				m_CanMoveCell = false;
			}
		}
		if (Input::IsKeyPressed(Key::Right))
		{
			if (m_CurrentCell.x < NumCellsX - 1)
			{
				m_CurrentCell.x++;
				m_CanMoveCell = false;
			}
		}

		if (Input::IsKeyPressed(Key::Space))
		{
			// Get the item index from the cell
			int32_t itemIndex = m_CurrentCell.x + m_CurrentCell.y * NumCellsX;
			if (itemIndex < m_NumItems)
			{
				// TODO: Use/Equip item
				std::string& itemToUse = m_ItemsLocationInGrid[itemIndex]->itemName;
				std::cout << itemToUse << std::endl;
			}
		}
	}

	if (!m_CanMoveCell)
	{
		m_CellMoveTimer += deltaTime;
		if (m_CellMoveTimer > 0.25) // 0.25 second
		{
			m_CanMoveCell = true;
			m_CellMoveTimer = 0.0f;
		}
	}
}

void Inventory::Render(Window* window)
{
	if (m_IsInventoryOpen)
	{
		// Render inventory outline
		m_InventorySprite->Draw(window);

		// Render inventory cell
		sf::Vector2f cellLocation = GetInventoryCellLocation(m_CurrentCell.x, m_CurrentCell.y);
		m_InventoryCellOutline.setPosition({cellLocation.x, cellLocation.y});
		window->GetWindowInstance()->draw(m_InventoryCellOutline);

		// Render the cell items
		int32_t itemNumber = 0;
		for (const auto& [name, item] : m_Items)
		{
			int32_t cellY = itemNumber / NumCellsX;
			int32_t cellX = itemNumber % NumCellsX;

			Sprite* itemIconSprite = item->itemIconSprite;
			itemIconSprite->SetScreenPosition(GetInventoryCellLocation(cellX, cellY));

			item->itemIconSprite->Draw(window);
			
			Text* itemCountText = item->itemCountText;
			itemCountText->SetPosition(GetInventoryCellLocation(cellX, cellY) + sf::Vector2f(2.0f, 2.0f)); // With a small offset
			itemCountText->Render(window);

			itemNumber++;
		}
		// Render the information about the item in the current cell
		int32_t cellIndex = m_CurrentCell.x + m_CurrentCell.y * NumCellsX;
		if (cellIndex < m_Items.size())
		{
			InventoryItem* currentItem = m_ItemsLocationInGrid[cellIndex];

			// Render the itemName text
			currentItem->itemNameText->Render(window);
			
			// Render the itemDescription text
			currentItem->itemDescriptionText->Render(window);
		}
	}
}

sf::Vector2f Inventory::GetInventoryCellLocation(int32_t cellX, int32_t cellY)
{
	sf::Vector2f inventoryCellArea = m_InventorySprite->GetScreenPosition() + InventoryCellAreaOffset;
	float cellXPos = inventoryCellArea.x + (cellX * InventoryCellDimension.x) + (cellX * InventoryCellGap.x);
	float cellYPos = inventoryCellArea.y + (cellY * InventoryCellDimension.y) + (cellY * InventoryCellGap.y);

	return sf::Vector2f(cellXPos, cellYPos);
}
