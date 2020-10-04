#include "Exception.h"
#include <stdarg.h>

lsoft::Exception::Exception(std::string &&whatStr) noexcept:
    _message(std::move(whatStr))
{
}

lsoft::Exception::Exception(const std::string &whatStr) noexcept:
    _message(whatStr)
{
}

lsoft::Exception::~Exception()
{
}

lsoft::Exception lsoft::Exception::printf(const char* fmt, ...)
{
    char buffer[2048];
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    return Exception(buffer);
}

const char *lsoft::Exception::what() const noexcept
{
    return _message.c_str();
}
