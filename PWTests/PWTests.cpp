#include <gtest/gtest.h>
#include <PWInventory.h>
#include <PWServer.h>
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

TEST(PWServerTest, shouldThrowIfFileCantBeOpened)
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
