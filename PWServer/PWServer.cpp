#include "PWServer.h"
#include "PWInventory.h"

#include <iostream>
#include <PWException.h>

PWServer::PWServer(const std::string& invFile,
				  const std::string& outFile)
	: invFile(invFile),outFile(outFile)
{
}

/**
 * @brief Starts the PWServer.
 * 
 * This function initializes the inventory, updates the quality of the items in the inventory,
 * and saves the updated inventory to a file.
 */
void PWServer::Start()
{
	//Init inventory
	std::unique_ptr<PWInventory> inventory = std::make_unique<PWInventory>();
	inventory->Load(invFile);

	//Update the inventory
	inventory->UpdateQuality();

    // Store the inventory
	inventory->Save(outFile);
}
