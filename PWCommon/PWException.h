#pragma once

#include <exception>

#define EXP_MESSAGE_MAX_LENGTH 1000
/**
 * @class PWException
 * @brief Custom exception class derived from std::exception.
 *
 * This class represents a custom exception that can be thrown in the application.
 * It inherits from the std::exception class and provides additional functionality.
 */
class PWException : public std::exception
{
private:
	char msg[EXP_MESSAGE_MAX_LENGTH];

public:
	/**
	 * @brief Constructs a PWException object with a formatted error message.
	 *
	 * This constructor takes a format string and additional arguments to construct
	 * the error message. The formatted error message is stored internally.
	 *
	 * @param fmt The format string for the error message.
	 * @param ... Additional arguments to be formatted into the error message.
	 */
	PWException(const char* fmt, ...);

	/**
	 * @brief Returns a C-style string describing the exception.
	 *
	 * This function returns the stored error message as a C-style string.
	 *
	 * @return A C-style string describing the exception.
	 */
	virtual char const* what() const noexcept;
};