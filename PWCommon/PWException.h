
/**
 * @file PWException.h
 * @brief Defines the PWException class, a custom exception class derived from std::exception.
 */

#pragma once

#include <exception>

#define EXP_MESSAGE_MAX_LENGTH 1000 /**< The maximum length of an error message. */

/**
 * @class PWException
 * @brief Custom exception class derived from std::exception.
 *
 * This class provides a custom exception type with the ability to store an error message of up to EXP_MESSAGE_MAX_LENGTH characters.
 */
class PWException : public std::exception
{
private:
	char msg[EXP_MESSAGE_MAX_LENGTH]; /**< The error message associated with the exception. */

public:
	/**
	 * @brief Constructs a PWException object with a formatted error message.
	 *
	 * @param fmt The format string for the error message.
	 * @param ... Additional arguments to be formatted into the error message.
	 */
	PWException(const char* fmt, ...);

	/**
	 * @brief Returns a C-style string describing the exception.
	 *
	 * @return A C-style string describing the exception.
	 */
	virtual char const* what() const noexcept override;
};
