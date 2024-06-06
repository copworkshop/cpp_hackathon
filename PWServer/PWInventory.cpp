#include "PWInventory.h"

void PWInventory::Save(const std::string& file)
{
	nlohmann::json inventoryArray = nlohmann::json::array();

	for (auto& invItem : items)
	{
		nlohmann::json jsonItem;

		jsonItem["name"] = invItem.name;
		jsonItem["sellby"] = invItem.sellBy;
		jsonItem["value"] = invItem.value;

		inventoryArray.push_back(jsonItem);
	}

	nlohmann::json inventoryJson;
	inventoryJson["inventory"] = inventoryArray;

	std::ofstream inventoryStream;
	inventoryStream.open(file.c_str());
	if (!inventoryStream) {
		throw PWException("failed to open inventory file at %s: ", file.c_str());
	}

	inventoryStream << inventoryJson.dump(2);
}

void PWInventory::Load(const std::string& file)
{
	std::ifstream inventoryStream;
	inventoryStream.open(file.c_str(), std::ios::in);
	if (!inventoryStream) {
		throw PWException("failed to open inventory file at %s: ", file.c_str());
	}

	nlohmann::json inventoryJson;
	inventoryStream >> inventoryJson;

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
        if (item.name == "Polka Dot Begonia")
        {
            UpdatePolkaDotBegonia(item);
        }
        else if (item.name == "Gardening Workshop")
        {
            UpdateGardeningWorkshop(item);
        }
        else
        {
            UpdateOtherItems(item);
        }
    }
}

void PWInventory::UpdatePolkaDotBegonia(InventoryItem& item)
{
    if (item.value < 50)
    {
        item.value++;
    }

    if (item.sellBy < 0 && item.value < 50)
    {
        item.value++;
    }

    item.sellBy--;
}

void PWInventory::UpdateGardeningWorkshop(InventoryItem& item)
{
    if (item.sellBy < 11 && item.value < 50)
    {
        item.value++;
    }

    if (item.sellBy < 0)
    {
        item.value = 0;
    }

    item.sellBy--;
}

void PWInventory::UpdateOtherItems(InventoryItem& item)
{
    if (item.value > 0 && item.name != "White Monstera")
    {
        item.value--;
    }

    if (item.sellBy < 0 && item.value > 0 && item.name != "White Monstera")
    {
        item.value--;
    }

    item.sellBy--;
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