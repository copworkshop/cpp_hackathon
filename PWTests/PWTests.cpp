#include <gtest/gtest.h>
#include <PWInventory.h>

#include <fstream>

// TIP: Keep the tests simple, aim for good coverage 
// TEST(PWInventory, FooBad) {
// 	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
// 	EXPECT_EQ(inventory[0].name, "Bar");
// }
TEST(PWInventory, FooGood) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
	EXPECT_EQ(inventory[0].name, "Foo");
}

TEST(PWInventory, LoadFileNotExist) {
	PWInventory inventory;
	std::string filename = "nonexistent_file.txt";
	EXPECT_THROW(inventory.Load(filename), PWException);
}

TEST(PWInventory, LoadFileExist) {
	PWInventory inventory;
	std::string filename = "existing_file.json";

	// Generate dummy JSON file
	std::ofstream file("existing_file.json");
	file << R"(
	{
		"inventory": [
			{
				"name": "Item1",
				"sellby": 10,
				"value": 6
			},
			{
				"name": "Item2",
				"sellby": 5,
				"value": 10
			},
			{
				"name": "Item3",
				"sellby": 3,
				"value": 13
			}
		]
	}
	)";
	file.close();
	EXPECT_NO_THROW(inventory.Load(filename));
}

