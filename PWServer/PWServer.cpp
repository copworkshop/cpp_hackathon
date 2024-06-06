#include "PWServer.h"
#include "PWInventory.h"

#include <iostream>
#include <PWException.h>
#include <nlohmann/json.hpp>

PWServer::PWServer(const std::string& invFile, const std::string& outFile)
    : invFile(invFile), outFile(outFile), useDatabase(false)
{
}

PWServer::PWServer(const std::string& invFile, const std::string& outFile, const nlohmann::json& dbConfig)
    : invFile(invFile), outFile(outFile), dbConfig(dbConfig), useDatabase(true)
{
    connectToDatabase();
}

void PWServer::connectToDatabase() {
    con = mysql_init(NULL);
    if (!mysql_real_connect(con, dbConfig["host"].get<std::string>().c_str(), dbConfig["user"].get<std::string>().c_str(), dbConfig["password"].get<std::string>().c_str(), dbConfig["database"].get<std::string>().c_str(), 0, NULL, 0)) {
        std::cerr << mysql_error(con) << std::endl;
        exit(1);
    }
}

void PWServer::readFromDatabase() {
    // Implement logic to read data from the database
}

void PWServer::writeToDatabase() {
    // Implement logic to write data to the database
}

void PWServer::Start() {
    std::unique_ptr<PWInventory> inventory = std::make_unique<PWInventory>();

    if (useDatabase) {
        readFromDatabase();
        // Update the inventory
        inventory->UpdateQuality();
        writeToDatabase();
    } else {
        inventory->Load(invFile);
        // Update the inventory
        inventory->UpdateQuality();
        inventory->Save(outFile);
    }
}