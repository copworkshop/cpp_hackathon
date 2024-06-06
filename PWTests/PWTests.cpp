#include <gtest/gtest.h>
#include <PWInventory.h>
 
// TIP: Keep the tests simple, aim for good coverage 
// TEST(PWInventory, FooBad) {
// 	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
// 	EXPECT_EQ(inventory[0].name, "Bar");
// }
TEST(PWInventory, FooGood) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
	EXPECT_EQ(inventory[0].name, "Foo");
}
 
#include <gtest/gtest.h>
#include <PWInventory.h>
#include <fstream>
#include <PWException.h>
 
// Test loading from a non-existent file
TEST(PWInventory, TestLoadNonExistentFile) {
    PWInventory inventory;
	ASSERT_THROW(inventory.Load("not existent file"), PWException);
}
 
// Test saving to a file and then loading from it
TEST(PWInventory, TestSaveAndLoad) {
    PWInventory inventory1{ { InventoryItem{ "Foo", 0 , 0 } } };
    inventory1.Save("test_file");
 
    PWInventory inventory2;
    inventory2.Load("test_file");
 
    ASSERT_EQ(inventory1[0].name, inventory2[0].name);
    ASSERT_EQ(inventory1[0].sellBy, inventory2[0].sellBy);
    ASSERT_EQ(inventory1[0].value, inventory2[0].value);
}
 
// Test updating quality for an item with negative sellIn
TEST(PWInventory, TestUpdateQualityNegativeSellIn) {
    PWInventory inventory{ { InventoryItem{ "Foo", -1 , 5 } } };
    inventory.UpdateQuality();
    ASSERT_LT(inventory[0].value, 5);
}
 
// Test updating quality for an item with zero quality
TEST(PWInventory, TestUpdateQualityZeroQuality) {
    PWInventory inventory{ { InventoryItem{ "Foo", 5 , 0 } } };
    inventory.UpdateQuality();
    ASSERT_EQ(inventory[0].value, 0);
}