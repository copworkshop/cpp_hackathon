#include <gtest/gtest.h>
#include <PWInventory.h>

// TIP: Keep the tests simple, aim for good coverage 

TEST(PWInventory, Save) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
	inventory.Save("test.json");
}

TEST(PWInventory, Load) {
	PWInventory inventory;
	inventory.Load("test.json");
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

