#include "PWException.h"

#include <cstdarg>
#include <cstdio>
#include <string>

PWException::PWException(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(msg, sizeof(msg), fmt, ap);
	va_end(ap);
}

PWException::PWException(const std::string& message)
{
	snprintf(msg, sizeof(msg), "%s", message.c_str());
}

const char* PWException::what() const noexcept
{
	return msg;
}