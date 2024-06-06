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

