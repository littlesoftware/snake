#ifndef LSOFT_EXCEPTION_H
#define LSOFT_EXCEPTION_H

#include <exception>
#include <string>

namespace lsoft {

class Exception: public std::exception
{
public:
    Exception(std::string&& whatStr) noexcept;
    Exception(const std::string& whatStr) noexcept;
    virtual ~Exception() noexcept;

    static Exception printf(const char* fmt, ...);

    virtual const char *what() const noexcept override;

private:
    std::string m_message;
};

} // namespace lsoft

#endif // LSOFT_EXCEPTION_H
