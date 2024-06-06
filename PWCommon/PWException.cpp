#include "PWException.h"

#include <cstdarg>
#include <cstdio>

/**
 * @brief Constructs a PWException object with a formatted error message.
 * 
 * This constructor takes a format string and a variable number of arguments, similar to the printf function.
 * It formats the error message using the provided format string and arguments, and stores it in the `msg` member variable.
 * 
 * @param fmt The format string for the error message.
 * @param ... The variable number of arguments to be formatted.
 */
PWException::PWException(const char* fmt, ...) : std::exception()
{
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(msg, sizeof(msg), fmt, ap);
	va_end(ap);
}

char const* PWException::what() const noexcept
{
	return msg;
}