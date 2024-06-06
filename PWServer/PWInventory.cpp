#include "PWInventory.h"

/**
 * Saves the inventory to a JSON file.
 *
 * @param file The path to the JSON file.
 */
void PWInventory::Save(const std::string& file)
{
	// build json
	nlohmann::json inventoryArray = nlohmann::json::array();

	for (auto& invItem : items)
	{
		nlohmann::json jsonItem;

		jsonItem["name"] = invItem.name;
		jsonItem["sellby"] = invItem.sellBy;
		jsonItem["value"] = invItem.value;

		inventoryArray.push_back(jsonItem);
	}

	//store items from repository collection to json tree
	nlohmann::json inventoryJson;
	inventoryJson["inventory"] = inventoryArray;

	//write json file
	std::ofstream inventoryStream;
	inventoryStream.open(file.c_str());
	if (!inventoryStream) {
		throw PWException("failed to open inventory file at %s: ", file.c_str());
	}

	//save json stream into file
	inventoryStream << inventoryJson.dump(2);
}

/**
 * @brief Loads the inventory data from a JSON file.
 * 
 * This function reads a JSON file and loads the inventory data into the repository collection.
 * The JSON file should have a root object named "inventory" containing an array of items.
 * Each item in the array should have the following properties: "name", "sellby", and "value".
 * 
 * @param file The path to the JSON file.
 * @throws PWException if the inventory file fails to open.
 */
void PWInventory::Load(const std::string& file)
{
	//read json file
	std::ifstream inventoryStream;
	inventoryStream.open(file.c_str(), std::ios::in);
	if (!inventoryStream) {
		throw PWException("failed to open inventory file at %s: ", file.c_str());
	}

	//load file into json stream
	nlohmann::json inventoryJson;
	inventoryStream >> inventoryJson;

	//get items from json and load into repository collection
	auto root = inventoryJson["inventory"];

	for (auto& jsonItem : root)
	{
		InventoryItem newItem;
		newItem.name = jsonItem["name"];
		newItem.sellBy = jsonItem["sellby"];
		newItem.value = jsonItem["value"];

		items.push_back(newItem);
	}
}

/**
 * @brief Updates the quality of the items in the inventory.
 * 
 * This function iterates through each item in the inventory and updates its quality based on certain conditions.
 * - If the item is not "Polka Dot Begonia" and not "Gardening Workshop":
 *   - If the item's value is greater than 0:
 *     - If the item is not "White Monstera", decrement the item's value by 1.
 * - If the item is "Polka Dot Begonia" or "Gardening Workshop":
 *   - If the item's value is less than 50:
 *     - Increment the item's value by 1.
 *   - If the item is "Gardening Workshop" and the sellBy value is less than 11:
 *     - If the item's value is less than 50, increment the item's value by 1.
 *   - If the item is "Gardening Workshop" and the sellBy value is less than 6:
 *     - If the item's value is less than 50, increment the item's value by 1.
 * - If the item is not "White Monstera", decrement the item's sellBy value by 1.
 * - If the item's sellBy value is less than 0:
 *   - If the item is not "Polka Dot Begonia" and not "Gardening Workshop":
 *     - If the item's value is greater than 0:
 *       - If the item is not "White Monstera", decrement the item's value by 1.
 *   - If the item is "Gardening Workshop", set the item's value to 0.
 *   - If the item is "Polka Dot Begonia" and the value is less than 50, increment the item's value by 1.
 */
void PWInventory::UpdateQuality()
{
	for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i].name != "Polka Dot Begonia" && items[i].name != "Gardening Workshop")
		{
			if (items[i].value > 0)
			{
				if (items[i].name != "White Monstera")
				{
					items[i].value = items[i].value - 1;
				}
			}
		}
		else
		{
			if (items[i].value < 50)
			{
				items[i].value = items[i].value + 1;

				if (items[i].name == "Gardening Workshop")
				{
					if (items[i].sellBy < 11)
					{
						if (items[i].value < 50)
						{
							items[i].value = items[i].value + 1;
						}
					}

					if (items[i].sellBy < 6)
					{
						if (items[i].value < 50)
						{
							items[i].value = items[i].value + 1;
						}
					}
				}
			}
		}

		if (items[i].name != "White Monstera")
		{
			items[i].sellBy = items[i].sellBy - 1;
		}

		if (items[i].sellBy < 0)
		{
			if (items[i].name != "Polka Dot Begonia")
			{
				if (items[i].name != "Gardening Workshop")
				{
					if (items[i].value > 0)
					{
						if (items[i].name != "White Monstera")
						{
							items[i].value = items[i].value - 1;
						}
					}
				}
				else
				{
					items[i].value = items[i].value - items[i].value;
				}
			}
			else
			{
				if (items[i].value < 50)
				{
					items[i].value = items[i].value + 1;
				}
			}
		}
	}
}

/**
 * @brief Overloaded subscript operator to access an item in the inventory by index.
 * 
 * @param index The index of the item to access.
 * @return A reference to the InventoryItem at the specified index.
 * @throws PWException if the index is out of range and the item is not found in the inventory.
 */
InventoryItem& PWInventory::operator[](int index)
{
	try
	{
		return items.at(index);
	}
	catch (const std::out_of_range&)
	{
		throw PWException("Item index %d is out of range not found in inventory\n", index);
	}
}

/**
 * Returns the number of items in the inventory.
 *
 * @return The number of items in the inventory.
 */
int PWInventory::Count() const
{
	return items.size();
}