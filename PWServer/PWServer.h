#pragma once

#include <string>

class PWServer
{
private:
	const std::string& invFile;
	const std::string& outFile;
	bool useDB;
public:
	PWServer(const std::string& invFile,const std::string& outFile, bool database = false);
	void Start();
};
