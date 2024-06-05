#include <mysql.h>

#include "PWInventory.h"

void PWInventory::Save(const std::string& file)
{
	if(_useSQL){
		std::ifstream inventoryStream;
		inventoryStream.open(file.c_str(), std::ios::in);
		if (!inventoryStream) {
			throw PWException("failed to open inventory file at %s: ", file.c_str());
		}

		//load file into json stream
		nlohmann::json inventoryJson;
		inventoryStream >> inventoryJson;
		const std::string server = inventoryJson["connectionString"];
		const std::string user = inventoryJson["user"];
		const std::string password = inventoryJson["password"];
		const std::string database = inventoryJson["database"];
		MYSQL *conn;

		// Initialize MySQL library
		mysql_library_init(0, NULL, NULL);

		// Establish a connection to the Azure SQL Database
		conn = mysql_init(NULL);
		if (!mysql_real_connect(conn, server.c_str(), user.c_str(), password.c_str(), database.c_str(), 0, NULL, 0)) {
			throw PWException("failed to connect to database: %s", mysql_error(conn));
		}

		// Iterate over the items collection
		for (auto& invItem : items)
		{
			// Prepare a SQL INSERT statement
			std::string query = "INSERT INTO inventory (name, sellby, value) VALUES ('" + invItem.name + "', '" + std::to_string(invItem.sellBy) + "', " + std::to_string(invItem.value) + ")";

			// Execute the SQL INSERT statement
			if (mysql_query(conn, query.c_str())) {
				throw PWException("failed to execute query: %s", mysql_error(conn));
			}
		}

		// Clean up
		mysql_close(conn);
		mysql_library_end();
	}
	else{
	
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
	if(_useSQL){
		const std::string server = inventoryJson["connectionString"];
		const std::string user = inventoryJson["user"];
		const std::string password = inventoryJson["password"];
		const std::string database = inventoryJson["database"];

		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;

		// Initialize MySQL library
		mysql_library_init(0, NULL, NULL);

		// Establish a connection to the Azure SQL Database
		conn = mysql_init(NULL);
		if (!mysql_real_connect(conn, server.c_str(), user.c_str(), password.c_str(), database.c_str(), 0, NULL, 0)) {
			throw PWException("failed to connect to database: %s", mysql_error(conn));
		}

		// Execute a SQL query to fetch the inventory data
		if (mysql_query(conn, "SELECT name, sellby, value FROM inventory")) {
			throw PWException("failed to execute query: %s", mysql_error(conn));
		}

		res = mysql_use_result(conn);

		// Parse the result set and load it into the items collection
		while ((row = mysql_fetch_row(res)) != NULL) {
			InventoryItem newItem;
			newItem.name = row[0];
			newItem.sellBy = std::stoi(row[1]);
			newItem.value = std::stoi(row[2]);

			items.push_back(newItem);
		}

		// Clean up
		mysql_free_result(res);
		mysql_close(conn);
		mysql_library_end();
	}
	else {
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