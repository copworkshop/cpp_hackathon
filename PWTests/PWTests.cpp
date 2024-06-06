#include <gtest/gtest.h>
#include <PWInventory.h>
#include <PWServer.h>

#include <fstream>

// TIP: Keep the tests simple, aim for good coverage 
// TEST(PWInventory, FooBad) {
// 	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
// 	EXPECT_EQ(inventory[0].name, "Bar");
// }

void CreateExampleFile(const std::string & filename)
{
	// Generate dummy JSON file
	std::ofstream file(filename);
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
}

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
	CreateExampleFile(filename);

	EXPECT_NO_THROW(inventory.Load(filename));
}

TEST(PWInventory, CountEmpty) {
	PWInventory inventory;
	EXPECT_EQ(inventory.Count(), 0);
}

TEST(PWInventory, CountNonEmpty) {
	PWInventory inventory{ { InventoryItem{ "Item1", 0 , 0 }, InventoryItem{ "Item2", 0 , 0 }, InventoryItem{ "Item3", 0 , 0 } } };
	EXPECT_EQ(inventory.Count(), 3);
}
TEST(PWInventory, OperatorThrow) {
	PWInventory inventory{ { InventoryItem{ "Item1", 0 , 0 }, InventoryItem{ "Item2", 0 , 0 }, InventoryItem{ "Item3", 0 , 0 } } };
	EXPECT_THROW(inventory[3], PWException);
}

TEST(PWInventory, OperatorNoThrow) {
	PWInventory inventory{ { InventoryItem{ "Item1", 0 , 0 }, InventoryItem{ "Item2", 0 , 0 }, InventoryItem{ "Item3", 0 , 0 } } };
	EXPECT_NO_THROW(inventory[0]);
	EXPECT_NO_THROW(inventory[1]);
	EXPECT_NO_THROW(inventory[2]);
}

TEST(PWInventory, SaveFileCannotOpen) {
	PWInventory inventory{ { InventoryItem{ "Item1", 0 , 0 }, InventoryItem{ "Item2", 0 , 0 }, InventoryItem{ "Item3", 0 , 0 } } };
	std::string filename{};
	EXPECT_THROW(inventory.Save(filename), PWException);
}

TEST(PWInventory, SaveFileSuccess) {
	PWInventory inventory{ { InventoryItem{ "Item1", 0 , 0 }, InventoryItem{ "Item2", 0 , 0 }, InventoryItem{ "Item3", 0 , 0 } } };
	std::string filename = "output_file.json";
	EXPECT_NO_THROW(inventory.Save(filename));

	// Verify that the file was created and contains the expected content
	std::ifstream file(filename);
	std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	std::string expectedContent = R"({
  "inventory": [
    {
      "name": "Item1",
      "sellby": 0,
      "value": 0
    },
    {
      "name": "Item2",
      "sellby": 0,
      "value": 0
    },
    {
      "name": "Item3",
      "sellby": 0,
      "value": 0
    }
  ]
})";

	EXPECT_EQ(fileContent, expectedContent);
}

TEST(PWException, MessageConstructor) {
	constexpr auto message = "Test exception message";
	PWException exception(message);
	EXPECT_STREQ(exception.what(), message);
}

TEST(PWInventory, UpdateQualityExpiredItem) {
	PWInventory inventory{ { InventoryItem{ "Expired Item", 0, 20 } } };
	inventory.UpdateQuality();
	EXPECT_EQ(inventory[0].sellBy, -1);
	EXPECT_EQ(inventory[0].value, 18);
}

TEST(PWInventory, UpdateQualityLegendaryItem) {
	PWInventory inventory{ { InventoryItem{ "Legendary Item", 10, 80 } } };
	inventory.UpdateQuality();
	EXPECT_EQ(inventory[0].sellBy, 9);
	EXPECT_EQ(inventory[0].value, 79);
}

TEST(PWInventory, UpdateQualityAgedBrie) {
	PWInventory inventory{ { InventoryItem{ "Aged Brie", 10, 20 } } };
	inventory.UpdateQuality();
	EXPECT_EQ(inventory[0].sellBy, 9);
	EXPECT_EQ(inventory[0].value, 19);
}

TEST(PWInventory, UpdateQualityBackstagePasses) {
	PWInventory inventory{ { InventoryItem{ "Backstage Passes", 10, 20 } } };
	inventory.UpdateQuality();
	EXPECT_EQ(inventory[0].sellBy, 9);
	EXPECT_EQ(inventory[0].value, 19);
}

TEST(PWInventory, UpdateQualityConjuredItem) {
	PWInventory inventory{ { InventoryItem{ "Conjured Item", 10, 20 } } };
	inventory.UpdateQuality();
	EXPECT_EQ(inventory[0].sellBy, 9);
	EXPECT_EQ(inventory[0].value, 19);
}

TEST(PWInventory, UpdateQualityPolkaDotBegonia) {
	PWInventory inventory{ { InventoryItem{ "Polka Dot Begonia", 10, 20 } } };
	inventory.UpdateQuality();
	EXPECT_EQ(inventory[0].sellBy, 9);
	EXPECT_EQ(inventory[0].value, 21);
}

TEST(PWServer, StartNoThrow) {
	std::string invfile = "existing_file.json";
	std::string outfile = "outfile_file.json";
	PWServer server(invfile, outfile);
	CreateExampleFile("existing_file.json");

	EXPECT_NO_THROW(server.Start());
}

TEST(PWInventory, UpdateQuality_GardeningWorkshopOver50) {
	PWInventory inventory{ { InventoryItem{ "Gardening Workshop", 10, 50 } } };
	inventory.UpdateQuality();
	EXPECT_EQ(inventory[0].sellBy, 9);
	EXPECT_EQ(inventory[0].value, 50);
}

TEST(PWInventory, UpdateQuality_GardeningWorkshopbelow50) {
	PWInventory inventory{ { InventoryItem{ "Gardening Workshop", 10, 49 } } };
	inventory.UpdateQuality();
	EXPECT_EQ(inventory[0].sellBy, 9);
	EXPECT_EQ(inventory[0].value, 50);
}

TEST(PWInventory, UpdateQuality_GardeningWorkshop_SellByBelow6_Value48) {
	PWInventory inventory{ { InventoryItem{ "Gardening Workshop", 5, 48 } } };
	inventory.UpdateQuality();
	EXPECT_EQ(inventory[0].sellBy, 4);
	EXPECT_EQ(inventory[0].value, 50);
}

TEST(PWInventory, UpdateQuality_GardeningWorkshop_SellByBelow6_Value49) {
	PWInventory inventory{ { InventoryItem{ "Gardening Workshop", 5, 49 } } };
	inventory.UpdateQuality();
	EXPECT_EQ(inventory[0].sellBy, 4);
	EXPECT_EQ(inventory[0].value, 50);
}

TEST(PWInventory, UpdateQuality_GardeningWorkshop_SellByBelow6_Value47) {
	PWInventory inventory{ { InventoryItem{ "Gardening Workshop", 5, 47 } } };
	inventory.UpdateQuality();
	EXPECT_EQ(inventory[0].sellBy, 4);
	EXPECT_EQ(inventory[0].value, 50);
}