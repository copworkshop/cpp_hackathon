#include "PWInventory.h"

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