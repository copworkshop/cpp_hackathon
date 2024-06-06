#pragma once

#include <exception>
#include <string>

#define EXP_MESSAGE_MAX_LENGTH 1000
class PWException : public std::exception
{
private:
	char msg[EXP_MESSAGE_MAX_LENGTH];


public:
	PWException(const char* fmt, ...);
	PWException(const std::string& message);
	virtual char const* what() const noexcept;
};
