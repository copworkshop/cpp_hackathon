#include "PWServer.h"
#include "PWInventory.h"

#include <iostream>
#include <PWException.h>

PWServer::PWServer(const std::string& invFile,
				  const std::string& outFile, bool database)
	: invFile(invFile),outFile(outFile), useDB(database)
{
}

void PWServer::Start()
{
	//Init inventory
	std::unique_ptr<PWInventory> inventory = std::make_unique<PWInventory>();
	inventory->useSQL(useDB);
	inventory->Load(invFile);

	//Update the inventory
	inventory->UpdateQuality();

    // Store the inventory
	inventory->Save(outFile);
}
