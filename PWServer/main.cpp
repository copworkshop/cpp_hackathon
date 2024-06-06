#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include <PWServer.h>
#include <PWException.h>

int main(int argc, char* argv[])
{
    std::string infile, outfile, dbfile;
    if (argc != 5 && argc != 7) {
        std::cerr << "Usage: " <<argv[0]<< " /infile <filename> /outfile <filename> [/db <dbfile>]"<<std::endl;
        return 1;
    }
    for (int i = 1; i < argc; i += 2) {
        std::string argName = argv[i];
        if (argName == "/infile") {
            infile = argv[i + 1];
        } else if (argName == "/outfile") {
            outfile = argv[i + 1];
        } else if (argName == "/db") {
            dbfile = argv[i + 1];
        } else {
            std::cerr << "Unknown argument: " << argName << std::endl;
            return 1;
        }
    }

    try
    {
        if (!dbfile.empty()) {
            // Read database configuration from file
			std::cout << "Reading database configuration from file: " << dbfile << std::endl;
            std::ifstream dbConfigFile(dbfile);
            nlohmann::json dbConfig;
            dbConfigFile >> dbConfig;

            // Print the database configuration
            std::cout << "Database configuration: " << dbConfig << std::endl;

            PWServer server(infile, outfile);
            server.Start();
        } else {
            PWServer server(infile, outfile);
            server.Start();
        }
    }
    catch (const PWException& exp)
    {
        std::cout << exp.what();
        return -1;
    }

    return 0;
}