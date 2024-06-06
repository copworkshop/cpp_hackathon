#include "PWInventory.h"
#include "gtest/gtest.h"

TEST(PWInventory, UpdateQuality_NormalItem)
{
    // Arrange
    PWInventory inventory{ { InventoryItem{ "Normal Item", 10, 20 } } };

    // Act
    inventory.UpdateQuality();

    // Assert
    EXPECT_EQ(inventory[0].sellBy, 9);
    EXPECT_EQ(inventory[0].value, 19); // Updated expected value
}

TEST(PWInventory, UpdateQuality_PolkaDotBegonia)
{
    // Arrange
    PWInventory inventory{ { InventoryItem{ "Polka Dot Begonia", 10, 20 } } };

    // Act
    inventory.UpdateQuality();

    // Assert
    EXPECT_EQ(inventory[0].sellBy, 9);
    EXPECT_EQ(inventory[0].value, 21); // Updated expected value
}

TEST(PWInventory, UpdateQuality_GardeningWorkshop_SellByLessThan11)
{
    // Arrange
    PWInventory inventory{ { InventoryItem{ "Gardening Workshop", 10, 20 } } };

    // Act
    inventory.UpdateQuality();

    // Assert
    EXPECT_EQ(inventory[0].sellBy, 9);
    EXPECT_EQ(inventory[0].value, 22); // Updated expected value
}

TEST(PWInventory, UpdateQuality_GardeningWorkshop_SellByLessThan6)
{
    // Arrange
    PWInventory inventory{ { InventoryItem{ "Gardening Workshop", 5, 20 } } };

    // Act
    inventory.UpdateQuality();

    // Assert
    EXPECT_EQ(inventory[0].sellBy, 4);
    EXPECT_EQ(inventory[0].value, 23);
}

TEST(PWInventory, UpdateQuality_WhiteMonstera)
{
    // Arrange
    PWInventory inventory{ { InventoryItem{ "White Monstera", 10, 20 } } };

    // Act
    inventory.UpdateQuality();

    // Assert
    EXPECT_EQ(inventory[0].sellBy, 10);
    EXPECT_EQ(inventory[0].value, 20);
}

TEST(PWInventory, UpdateQuality_SellByLessThan0_NormalItem)
{
    // Arrange
    PWInventory inventory{ { InventoryItem{ "Normal Item", -1, 20 } } };

    // Act
    inventory.UpdateQuality();

    // Assert
    EXPECT_EQ(inventory[0].sellBy, -2);
    EXPECT_EQ(inventory[0].value, 18);
}

TEST(PWInventory, UpdateQuality_SellByLessThan0_PolkaDotBegonia)
{
    // Arrange
    PWInventory inventory{ { InventoryItem{ "Polka Dot Begonia", -1, 20 } } };

    // Act
    inventory.UpdateQuality();

    // Assert
    EXPECT_EQ(inventory[0].sellBy, -2);
    EXPECT_EQ(inventory[0].value, 22);
}

TEST(PWInventory, UpdateQuality_SellByLessThan0_GardeningWorkshop)
{
    // Arrange
    PWInventory inventory{ { InventoryItem{ "Gardening Workshop", -1, 20 } } };

    // Act
    inventory.UpdateQuality();

    // Assert
    EXPECT_EQ(inventory[0].sellBy, -2);
    EXPECT_EQ(inventory[0].value, 0);
}

TEST(PWInventory, UpdateQuality_SellByLessThan0_WhiteMonstera)
{
    // Arrange
    PWInventory inventory{ { InventoryItem{ "White Monstera", -1, 20 } } };

    // Act
    inventory.UpdateQuality();

    // Assert
    EXPECT_EQ(inventory[0].sellBy, -1);
    EXPECT_EQ(inventory[0].value, 20);
}TEST(PWInventory, UpdateQuality_DecreaseValue)
{
    // Arrange
    PWInventory inventory{ { InventoryItem{ "Normal Item", 10, 20 } } };

    // Act
    inventory.UpdateQuality();

    // Assert
    EXPECT_EQ(inventory[0].value, 19);
}