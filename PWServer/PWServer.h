/**
 * @file PWServer.h
 * @brief This file contains the PWServer class.
 */

#pragma once

#include <string>

/**
 * @class PWServer
 * @brief This class represents a PWServer.
 */
class PWServer
{
private:
	/**
	 * @brief The inventory file.
	 */
	const std::string& invFile;

	/**
	 * @brief The output file.
	 */
	const std::string& outFile;

public:
	/**
	 * @brief Constructs a PWServer with the specified inventory and output files.
	 * @param invFile The inventory file.
	 * @param outFile The output file.
	 */
	PWServer(const std::string& invFile,const std::string& outFile);

	/**
	 * @brief Starts the PWServer.
	 */
	void Start();
};