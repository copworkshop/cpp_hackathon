#include <gtest/gtest.h>
#include <PWInventory.h>
#include <fstream>
#include <PWException.h>
 
// TIP: Keep the tests simple, aim for good coverage 
// TEST(PWInventory, FooBad) {
// 	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
// 	EXPECT_EQ(inventory[0].name, "Bar");
// }
TEST(PWInventory, FooGood) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
	EXPECT_EQ(inventory[0].name, "Foo");
}
  
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

// Test updating quality for an item with positive sellIn and positive quality
TEST(PWInventory, TestUpdateQualityPositiveSellInPositiveQuality) {
	PWInventory inventory{ { InventoryItem{ "Foo", 5 , 10 } } };
	inventory.UpdateQuality();
	ASSERT_GT(inventory[0].value, 0);
	ASSERT_LT(inventory[0].value, 10);
}

// Test updating quality for an item with positive sellIn and maximum quality
TEST(PWInventory, TestUpdateQualityPositiveSellInMaxQuality) {
	PWInventory inventory{ { InventoryItem{ "Foo", 5 , 50 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 49);
}

// Test updating quality for an item with zero sellIn and positive quality
TEST(PWInventory, TestUpdateQualityZeroSellInPositiveQuality) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 10 } } };
	inventory.UpdateQuality();
	ASSERT_LT(inventory[0].value, 10);
}

// Test updating quality for an item with zero sellIn and maximum quality
TEST(PWInventory, TestUpdateQualityZeroSellInMaxQuality) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 50 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 48);
}

// Test updating quality for an item with negative sellIn and maximum quality
TEST(PWInventory, TestUpdateQualityNegativeSellInMaxQuality) {
	PWInventory inventory{ { InventoryItem{ "Foo", -1 , 50 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 48);
}

// Test updating quality for multiple items
TEST(PWInventory, TestUpdateQualityMultipleItems) {
	PWInventory inventory{ { InventoryItem{ "Foo", 5 , 10 }, InventoryItem{ "Bar", 3 , 20 } } };
	inventory.UpdateQuality();
	ASSERT_GT(inventory[0].value, 0);
	ASSERT_LT(inventory[0].value, 10);
	ASSERT_GT(inventory[1].value, 0);
	ASSERT_LT(inventory[1].value, 20);
}

// Test updating quality for items not named "Polka Dot Begonia" or "Gardening Workshop" with positive value
TEST(PWInventory, TestUpdateQualityNotPolkaDotBegoniaOrGardeningWorkshopPositiveValue) {
	PWInventory inventory{ { InventoryItem{ "Foo", 5 , 10 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 9);
}

// Test updating quality for items not named "Polka Dot Begonia" or "Gardening Workshop" with zero value
TEST(PWInventory, TestUpdateQualityNotPolkaDotBegoniaOrGardeningWorkshopZeroValue) {
	PWInventory inventory{ { InventoryItem{ "Foo", 5 , 0 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 0);
}

// Test updating quality for items named "Polka Dot Begonia" or "Gardening Workshop" with value less than 50
TEST(PWInventory, TestUpdateQualityPolkaDotBegoniaOrGardeningWorkshopValueLessThan50) {
	PWInventory inventory{ { InventoryItem{ "Polka Dot Begonia", 5 , 49 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 50);
}

// Test updating quality for items named "Polka Dot Begonia" or "Gardening Workshop" with value equal to 50
TEST(PWInventory, TestUpdateQualityPolkaDotBegoniaOrGardeningWorkshopValueEqualTo50) {
	PWInventory inventory{ { InventoryItem{ "Gardening Workshop", 5 , 50 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 50);
}

// Test updating quality for items named "Gardening Workshop" with sellBy less than 11 and value less than 50
TEST(PWInventory, TestUpdateQualityGardeningWorkshopSellByLessThan11ValueLessThan50) {
	PWInventory inventory{ { InventoryItem{ "Gardening Workshop", 10 , 49 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 50);
}

// Test updating quality for items named "Gardening Workshop" with sellBy less than 6 and value less than 50
TEST(PWInventory, TestUpdateQualityGardeningWorkshopSellByLessThan6ValueLessThan50) {
	PWInventory inventory{ { InventoryItem{ "Gardening Workshop", 5 , 49 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 50);
}

// Test updating quality for items not named "White Monstera" with positive sellBy
TEST(PWInventory, TestUpdateQualityNotWhiteMonsteraPositiveSellBy) {
	PWInventory inventory{ { InventoryItem{ "Foo", 5 , 10 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].sellBy, 4);
}

// Test updating quality for items named "White Monstera" with positive sellBy
TEST(PWInventory, TestUpdateQualityWhiteMonsteraPositiveSellBy) {
	PWInventory inventory{ { InventoryItem{ "White Monstera", 5 , 10 } } };
	inventory.UpdateQuality();
	ASSERT_NE(inventory[0].sellBy, 4);
}

// Test updating quality for items with sellBy less than 0 and not named "Polka Dot Begonia" or "Gardening Workshop" with positive value
TEST(PWInventory, TestUpdateQualitySellByLessThan0NotPolkaDotBegoniaOrGardeningWorkshopPositiveValue) {
	PWInventory inventory{ { InventoryItem{ "Foo", -1 , 10 } } };
	inventory.UpdateQuality();
	ASSERT_NE(inventory[0].value, 9);
}

// Test updating quality for items with sellBy less than 0 and not named "Polka Dot Begonia" or "Gardening Workshop" with zero value
TEST(PWInventory, TestUpdateQualitySellByLessThan0NotPolkaDotBegoniaOrGardeningWorkshopZeroValue) {
	PWInventory inventory{ { InventoryItem{ "Foo", -1 , 0 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 0);
}

// Test updating quality for items with sellBy less than 0 and named "Polka Dot Begonia" with value less than 50
TEST(PWInventory, TestUpdateQualitySellByLessThan0PolkaDotBegoniaValueLessThan50) {
	PWInventory inventory{ { InventoryItem{ "Polka Dot Begonia", -1 , 49 } } };
	inventory.UpdateQuality();
	ASSERT_NE(inventory[0].value, 50);
}

// Test updating quality for items with sellBy less than 0 and named "Polka Dot Begonia" with value equal to 50
TEST(PWInventory, TestUpdateQualitySellByLessThan0PolkaDotBegoniaValueEqualTo50) {
	PWInventory inventory{ { InventoryItem{ "Polka Dot Begonia", -1 , 50 } } };
	inventory.UpdateQuality();
	ASSERT_NE(inventory[0].value, 50);
}

// Test updating quality for items with sellBy less than 0 and named "Gardening Workshop" with value less than 50
TEST(PWInventory, TestUpdateQualitySellByLessThan0GardeningWorkshopValueLessThan50) {
	PWInventory inventory{ { InventoryItem{ "Gardening Workshop", -1 , 49 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 0);
}

// Test updating quality for items with sellBy less than 0 and named "Gardening Workshop" with value equal to 50
TEST(PWInventory, TestUpdateQualitySellByLessThan0GardeningWorkshopValueEqualTo50) {
	PWInventory inventory{ { InventoryItem{ "Gardening Workshop", -1 , 50 } } };
	inventory.UpdateQuality();
	ASSERT_EQ(inventory[0].value, 0);
}
// Test saving inventory to file
TEST(PWInventory, TestSaveInventoryToFile) {
    PWInventory inventory{ { InventoryItem{ "Foo", 5 , 10 } } };
    inventory.Save("test_inventory.json");

    // Verify that the file exists
    std::ifstream file("test_inventory.json");
    ASSERT_TRUE(file.good());

    // Read the file and verify its contents
    nlohmann::json inventoryJson;
    file >> inventoryJson;

    ASSERT_TRUE(inventoryJson.contains("inventory"));
    ASSERT_EQ(inventoryJson["inventory"].size(), 1);

    auto jsonItem = inventoryJson["inventory"][0];
    ASSERT_TRUE(jsonItem.contains("name"));
    ASSERT_TRUE(jsonItem.contains("sellby"));
    ASSERT_TRUE(jsonItem.contains("value"));

    ASSERT_EQ(jsonItem["name"], "Foo");
    ASSERT_EQ(jsonItem["sellby"], 5);
    ASSERT_EQ(jsonItem["value"], 10);
}