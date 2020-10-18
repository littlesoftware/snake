#ifndef LSOFT_LOG_LOGGER_H
#define LSOFT_LOG_LOGGER_H

#include "Options.h"
#include "common/NoCopyable.h"

#include <string>
#include <sstream>
#include <mutex>

namespace lsoft {
namespace log {

/*
 * Logger
 * Event logging type
 *
 */

class Logger: public NoCopyable
{
public:
    explicit Logger(const std::string& name);
    ~Logger();

    template<typename T>
    void trace(const T& message) {
        translateToLog(message, Type::TRACE);
    }

    template<typename T>
    void debug(const T& message) {
        translateToLog(message, Type::DEBUG);
    }

    template<typename T>
    void info(const T& message) {
        translateToLog(message, Type::INFO);
    }

    template<typename T>
    void warning(const T& message) {
        translateToLog(message, Type::WARNING);
    }

    template<typename T>
    void error(const T& message) {
        translateToLog(message, Type::ERROR);
    }

    template<typename T>
    void critical(const T& message) {
        translateToLog(message, Type::CRITICAL);
    }

    template<typename T>
    Logger& operator<< (const T& message) {
        translateToLog(message, Type::DEBUG);
        return *this;
    }

    void printf(const Type type, const char* fmt, ...);
    void printf(const char* fmt, ...);

    static std::string toHex(const void* data, size_t size);

    static Logger& system();

private:
    Logger();

    template<typename T>
    inline void translateToLog(const T& message, Type type) {
        std::ostringstream buffer;
        buffer << message;
        makeLog(buffer.str(), type);
    }

    void makeLog(const std::string& message, const Type type);
    inline void beginSegment();
    inline void endSegment();
    inline const char *stringOfLevel(Type type);
    inline void printColorOfType(std::ostream &os, Type type);
    inline void printResetColor(std::ostream &os);
    inline void printDateTime(std::ostream &os, uint32_t flags);
    inline void printThreadId(std::ostream &os);

    // --------------------------------------------------------------
    // Member data
    // --------------------------------------------------------------
    static std::mutex m_mutex;
    bool m_segment{true};
    std::string m_name;
};

}} // namespace lsoft::log

#endif // LSOFT_LOG_LOGGER_H
