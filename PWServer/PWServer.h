#pragma once

#include <string>

/**
 * @class PWServer
 * @brief Represents a server for processing password files.
 *
 * The PWServer class provides functionality for starting a server that processes password files.
 * It takes an input file and an output file as parameters and provides a method to start the server.
 */
class PWServer
{
private:
	const std::string& invFile; /**< The input file path. */
	const std::string& outFile; /**< The output file path. */

public:
	/**
	 * @brief Constructs a PWServer object with the specified input and output file paths.
	 * @param invFile The input file path.
	 * @param outFile The output file path.
	 */
	PWServer(const std::string& invFile, const std::string& outFile);

	/**
	 * @brief Starts the server for processing password files.
	 */
	void Start();
};
