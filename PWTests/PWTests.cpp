#include <gtest/gtest.h>
#include <PWInventory.h>
#include <PWException.h>
#include <string>

// TIP: Keep the tests simple, aim for good coverage 

TEST(PWInventory, Save) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
	inventory.Save("test.json");
}

TEST(PWInventory, Save_Exception) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
	EXPECT_THROW({
		try {
			inventory.Save("/nonexistent_directory/test.json");
		}
		catch (const PWException& ex) {
			EXPECT_TRUE(std::string(ex.what()).find("failed to open inventory file") != std::string::npos);
			throw;
		}
	}, PWException);
}

TEST(PWInventory, Load) {
	PWInventory inventory;
	inventory.Load("test.json");
}

TEST(PWInventory, Load_Exception) {

	PWInventory inventory;

	EXPECT_THROW({
		try {
			inventory.Load("nonexistent.json");
		}
		catch (const PWException& ex) {
			EXPECT_TRUE(std::string(ex.what()).find("File does not exist") != std::string::npos);
			throw;
		}
	}, PWException);

}

TEST(PWInventory, Load_Parse_Exception) {

	PWInventory inventory;
	std::ofstream inventoryStream;
	inventoryStream.open("empty.json");
	inventoryStream << "";

	EXPECT_THROW({
		try {
			inventory.Load("empty.json");
		}
		catch (const PWException& ex) {
			EXPECT_TRUE(std::string(ex.what()).find("Failed to parse JSON") != std::string::npos);
			throw;
		}
	}, PWException);

}

TEST(PWInventory, UpdateQuality) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
	inventory.UpdateQuality();
}

TEST(PWInventory, Operator) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
	InventoryItem item = inventory[0];
	EXPECT_EQ(item.name, "Foo");
}

TEST(PWInventory, FooGood) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
	EXPECT_EQ(inventory[0].name, "Foo");
}

TEST(PWInventory, Count) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
	EXPECT_EQ(inventory.Count(), 1);
}

class PWInventoryTest : public ::testing::TestWithParam<std::tuple<std::string, int, int, int, int>> {
};

TEST_P(PWInventoryTest, UpdateQuality) {
    auto [name, sellBy, value, expectedSellBy, expectedValue] = GetParam();
    PWInventory inventory{ { InventoryItem{ name, sellBy, value } } };
    inventory.UpdateQuality();
    EXPECT_EQ(inventory[0].sellBy, expectedSellBy);
    EXPECT_EQ(inventory[0].value, expectedValue);
}

INSTANTIATE_TEST_SUITE_P(
    PWInventoryTests,
    PWInventoryTest,
    ::testing::Values(
        // Test for "Polka Dot Begonia"
        std::make_tuple("Polka Dot Begonia", 10, 10, 9, 11),
        std::make_tuple("Polka Dot Begonia", 0, 10, -1, 12),
        std::make_tuple("Polka Dot Begonia", -1, 50, -2, 50),
        std::make_tuple("Polka Dot Begonia", -1, 51, -2, 51),

        // Test for "Gardening Workshop"
        std::make_tuple("Gardening Workshop", 10, 10, 9, 12),
        std::make_tuple("Gardening Workshop", 5, 10, 4, 13),
        std::make_tuple("Gardening Workshop", 0, 10, -1, 0),

        // Test for "White Monstera"
        std::make_tuple("White Monstera", 10, 10, 10, 10),
        std::make_tuple("White Monstera", 0, 10, 0, 10),

        // Test for other items
        std::make_tuple("Other Item", 10, 10, 9, 9),
        std::make_tuple("Other Item", 0, 10, -1, 8)
    )
);
