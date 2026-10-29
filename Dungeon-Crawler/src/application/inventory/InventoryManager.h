#pragma once
#include "InventoryItem.h"
#include <unordered_map>
#include <iostream>
#include <string>

// Stores a database of item name -> item struct
class InventoryManager
{
private:
	std::unordered_map<std::string, InventoryItem*> m_Items;

public:
	InventoryManager();

	void PushItemIntoDatabase(const std::string& itemName, InventoryItem* item);

	InventoryItem* GetItemFromName(const std::string& itemName);
};