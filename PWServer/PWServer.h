#pragma once

#include <string>
#include <string>
#include <nlohmann/json.hpp>
#include <mysql.h>

/**
 * @class PWServer
 * @brief Represents a server for processing inventory files and generating output files.
 */
class PWServer
{
private:
    const std::string& invFile; /**< The path to the input inventory file. */
    const std::string& outFile; /**< The path to the output file. */
        void connectToDatabase();
    void readFromDatabase();
    void writeToDatabase();
    nlohmann::json dbConfig;
    bool useDatabase;
    MYSQL *con;

public:
    /**
     * @brief Constructs a PWServer object with the specified input and output file paths.
     * @param invFile The path to the input inventory file.
     * @param outFile The path to the output file.
     */
    PWServer(const std::string& invFile, const std::string& outFile);
    PWServer(const std::string& invFile, const std::string& outFile, const nlohmann::json& dbConfig);
 

    /**
     * @brief Starts the server and begins processing the inventory file.
     */
    void Start();
};