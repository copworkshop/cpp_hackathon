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
        UpdateItemQuality(items[i]);
    }
}

void PWInventory::UpdateItemQuality(InventoryItem& item)
{
    if (item.name == "Polka Dot Begonia" || item.name == "Gardening Workshop")
    {
        UpdateSpecialItemQuality(item);
    }
    else
    {
        UpdateRegularItemQuality(item);
    }

    if (item.name != "White Monstera")
    {
        item.sellBy--;
    }

    if (item.sellBy < 0)
    {
        UpdateExpiredItemQuality(item);
    }
}

void PWInventory::UpdateRegularItemQuality(InventoryItem& item)
{
    if (item.value > 0 && item.name != "White Monstera")
    {
        item.value--;
    }
}

void PWInventory::UpdateSpecialItemQuality(InventoryItem& item)
{
    if (item.value < 50)
    {
        item.value++;

        if (item.name == "Gardening Workshop" && item.sellBy < 11 && item.value < 50)
        {
            item.value++;
        }

        if (item.name == "Gardening Workshop" && item.sellBy < 6 && item.value < 50)
        {
            item.value++;
        }
    }
}

void PWInventory::UpdateExpiredItemQuality(InventoryItem& item)
{
    if (item.name == "Polka Dot Begonia")
    {
        item.value++;
    }
    else if (item.name != "Gardening Workshop" && item.value > 0 && item.name != "White Monstera")
    {
        item.value--;
    }
    else
    {
        item.value = 0;
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