#include "InventoryManager.h"

#include "InventoryItem.h"

InventoryManager::InventoryManager()
{
}

void InventoryManager::PushItemIntoDatabase(const std::string& itemName, InventoryItem* item)
{
	m_Items[itemName] = item;
}

InventoryItem* InventoryManager::GetItemFromName(const std::string& itemName)
{
	return m_Items[itemName];
}
