#include "PWInventory.h"

namespace {
void decrementSellBy(InventoryItem& item)
{
	item.sellBy -= item.name != "White Monstera" ? 1 : 0;
}

void applyDiscount(InventoryItem& item)
{
	if(item.sellBy >=0) return;
	
	if (item.name == "Polka Dot Begonia") { item.value = std::min(item.value + 1, 50); return; }

	if (item.name == "Gardening Workshop") { item.value = 0; return; }

	if (item.name == "White Monstera") return;

	item.value = std::max(item.value - 1, 0);
}
}

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

void PWInventory::UpdateQuality()
{
	for (auto& item : items)
	{
		if (item.name != "Polka Dot Begonia" && item.name != "Gardening Workshop")
		{
			if (item.value > 0 && item.name != "White Monstera")
			{
				item.value--;
			}
		}
		else
		{
			if (item.value < 50)
			{
				item.value++;

				if (item.name == "Gardening Workshop")
				{
					if (item.sellBy < 11 && item.value < 50)
					{
						item.value++;
					}

					if (item.sellBy < 6 && item.value < 50)
					{
						item.value++;
					}
				}
			}
		}


		decrementSellBy(item);
		applyDiscount(item);
	}
}

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

int PWInventory::Count() const
{
	return items.size();
}