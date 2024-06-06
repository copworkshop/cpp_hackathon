#include "PWInventory.h"
#include "PWException.h"
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>


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
	if (!std::filesystem::exists(file)) {
		throw PWException("File does not exist: " + file);
	}

	std::ifstream inventoryStream(file.c_str(), std::ios::in);

	if (!inventoryStream) {
		throw PWException("Failed to open inventory file: " + file);
	}

	nlohmann::json inventoryJson;
	try {
		inventoryStream >> inventoryJson;
	} catch (nlohmann::json::parse_error& e) {
		throw PWException("Failed to parse JSON: " + std::string(e.what()));
	}

	auto root = inventoryJson["inventory"];

	for (auto& jsonItem : root)
	{
		if (!jsonItem.contains("name") || !jsonItem.contains("sellby") || !jsonItem.contains("value")) {
			throw PWException("Invalid JSON format");
		}

		InventoryItem newItem;
		newItem.name = jsonItem["name"];
		newItem.sellBy = jsonItem["sellby"];
		newItem.value = jsonItem["value"];

		items.push_back(newItem);
	}
}

void PWInventory::UpdateQualityForNormalItem(InventoryItem& item)
{
    if (item.value > 0)
    {
        item.value--;
    }
    if (item.sellBy < 0 && item.value > 0)
    {
        item.value--;
    }
}

void PWInventory::UpdateQualityForSpecialItem(InventoryItem& item)
{
    if (item.value < 50)
    {
        item.value++;
        if (item.sellBy < 11 && item.value < 50)
        {
            item.value++;
        }
        if (item.sellBy < 6 && item.value < 50)
        {
            item.value++;
        }
    }
    if (item.sellBy < 0)
    {
        item.value = 0;
    }
}

void PWInventory::UpdateQuality()
{
    for (auto& item : items)
    {
        if (item.name == "Polka Dot Begonia" || item.name == "Gardening Workshop")
        {
            UpdateQualityForSpecialItem(item);
        }
        else if (item.name != "White Monstera")
        {
            UpdateQualityForNormalItem(item);
        }

        if (item.name != "White Monstera")
        {
            item.sellBy--;
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