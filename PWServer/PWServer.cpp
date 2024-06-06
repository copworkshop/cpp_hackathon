#include "PWServer.h"
#include "PWInventory.h"

#include <iostream>
#include <PWException.h>

PWServer::PWServer(const std::string& invFile,
				  const std::string& outFile)
	: invFile(invFile),outFile(outFile)
{
}

void PWServer::Start()
{
	//Init inventory
	// TODO: Refactor to allow mock injection, but PWInventory has operator[] function
	// which is not supported by gmock to be mocked so it needs another refactor.
	std::unique_ptr<PWInventory> inventory = std::make_unique<PWInventory>();
	inventory->Load(invFile);

	//Update the inventory
	inventory->UpdateQuality();

    // Store the inventory
	inventory->Save(outFile);
}
