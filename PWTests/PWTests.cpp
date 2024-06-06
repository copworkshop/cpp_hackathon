#include <gtest/gtest.h>
#include <PWInventory.h>
#include <PWServer.h>
#include <PWException.h>
#include <gmock/gmock.h>

// TIP: Keep the tests simple, aim for good coverage 
// TEST(PWInventory, FooBad) {
// 	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
// 	EXPECT_EQ(inventory[0].name, "Bar");
// }
using namespace ::testing;
TEST(PWInventory, FooGood) {
	PWInventory inventory{ { InventoryItem{ "Foo", 0 , 0 } } };
	EXPECT_EQ(inventory[0].name, "Foo");
}

TEST(PWInventory, LoadShouldThrowIfCantLoad) {
	PWInventory inventory;
	std::string filename = "non_existent_file.txt";

	// Expect Load to throw a std::exception when it fails to load from a non-existent file
	EXPECT_THROW(inventory.Load(filename), std::exception);
}

TEST(PWInventory, LoadShouldLoadSampleFile) {
	PWInventory inventory;
	std::string filename = "../../../PWServer/inventory.json";

	inventory.Load(filename);
	EXPECT_EQ(5, inventory.Count());
}

TEST(PWServerTest, shouldThrowIfFileCouldntBeOpen)
{
    // Arrange
    std::string invFile = "input_inventory.txt";
    std::string outFile = "output_file.txt";
    PWServer server(invFile, outFile);

    // Act
	EXPECT_THROW(server.Start(), std::exception);
}

TEST(PWException, ConstructorWithMessage)
{
	// Arrange
	const char* errorMessage = "An error occurred";

	// Act
	PWException exception(errorMessage);

	// Assert
	EXPECT_STREQ(exception.what(), errorMessage);
}
