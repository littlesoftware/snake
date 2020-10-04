#include "Logger.h"
#include "common/system.h"

#include <iomanip>
#include <chrono>
#include <thread>
#include <stdarg.h>

#if defined(LSOFT_WINDOWS)
#include <windows.h>
#undef ERROR
#endif

std::mutex lsoft::log::Logger::_mutex;

lsoft::log::Logger::Logger(const std::string& name):
    _name(name)
{
    beginSegment();
}

lsoft::log::Logger::~Logger()
{
    if(_segment)
        endSegment();
}

void lsoft::log::Logger::printf(const lsoft::log::Type type, const char* fmt, ...)
{
    char buffer[2048];
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    makeLog(buffer, type);
}

void lsoft::log::Logger::printf(const char* fmt, ...)
{
    char buffer[2048];
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    makeLog(buffer, Type::DEBUG);
}

std::string lsoft::log::Logger::toHex(const void *data, size_t size)
{
    static const char * prefix = "  ";
    char descBuffer[17];
    std::ostringstream output;
    // make header
    output << std::endl
           << prefix << "         | 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f |                 " << std::endl
           << prefix << "---------+-------------------------------------------------+-----------------" << std::endl;
    // make body
    size_t lineNumber = 0;
    size_t symbol = 0;
    const uint8_t* pointer = static_cast<const uint8_t*>(data);
    const uint8_t* end = pointer+size;
    descBuffer[16] = 0;
    while( pointer!=end )
    {
        // if it is first symbol
        if(symbol == 0)
        {
            output << prefix << std::setw(8) << std::setfill('0') << std::hex << lineNumber << " | ";
            lineNumber+=16;
        }
        // print a symbol
        output << std::setw(2) << static_cast<uint16_t>(*pointer) << " ";
        descBuffer[symbol] = pointer[0]>0x1f && pointer[0]<0x7f ? pointer[0] : '.' ;
        // last action?
        pointer++;
        if( pointer == end )
        {
            while(++symbol < 16)
            {
                output << "   ";
                descBuffer[symbol] = ' ';
            }
            symbol--;
        }
        // print of symbols
        symbol++;
        symbol%=16;
        if(symbol == 0)
        {
            output << "| " << descBuffer << std::endl;
        }
    }
    // make footer
    output << prefix << "total " << std::dec << size << " bytes";
    // return the result
    return output.str();
}

lsoft::log::Logger &lsoft::log::Logger::system()
{
    static Logger logger;
    return logger;
}

lsoft::log::Logger::Logger():
    _segment(false),
    _name("System")
{
}

void lsoft::log::Logger::makeLog(const std::string& message, const Type type)
{
    Options& options = Options::instance();

    if(type < options.lowType())
        return;
    std::ostringstream output;
    uint32_t flags = options.flags();
    bool hasColor = flags & Flag::COLOR;

    // print header
    if( flags & Flag::DATETIME )
        printDateTime(output, flags);
    if( flags & Flag::THREAD )
        printThreadId(output);
    if( flags & Flag::NAME )
        output << _name << " ";
    if( flags & Flag::TYPE )
        output << stringOfLevel(type) << " ";

    if( flags & Flag::SEPARATION )
        output << ": " << message;
    else
        output << message;

    // print message
    {
        std::lock_guard<std::mutex> lockOutput(_mutex);
        std::ostream& stream = type>=Type::ERROR ? options.error() : options.output();
        // if has coloring
        if(hasColor)
        {
            printColorOfType(stream, type);
            stream << output.str();
            printResetColor(stream);
            stream << std::endl;
        } else {
            stream << output.str() << std::endl;
        }
    }

    if(type >= Type::CRITICAL)
    {
        options.output() << std::flush;
        options.error() << std::flush;
        std::exit(1);
    }
}

void lsoft::log::Logger::beginSegment()
{
    makeLog("begin", Type::SEGMENT);
}

void lsoft::log::Logger::endSegment()
{
    makeLog("end", Type::SEGMENT);
}

const char* lsoft::log::Logger::stringOfLevel(Type type)
{
    static const char* levelStrings[] = {"T", "+", "D", "I", "W", "E", "C"};
    return levelStrings[static_cast<uint32_t>(type)];
}

void lsoft::log::Logger::printColorOfType(std::ostream &os, Type type)
{
#if defined(LSOFT_POSIX)
    static const char* colorStrings[] = {"\033[0;37m",
                                         "\033[0;36m",
                                         "\033[1;37m",
                                         "\033[1;32m",
                                         "\033[1;33m",
                                         "\033[1;31m",
                                         "\033[1;37m\033[0;41m"};
    os << colorStrings[static_cast<uint32_t>(type)];
#elif defined(LSOFT_WINDOWS)
    static WORD colorWords[] = {0x08, 0x0B, 0x0F, 0x0A, 0x0E, 0x0C, 0xCF};
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorWords[static_cast<uint32_t>(type)]);
#endif
}

void lsoft::log::Logger::printResetColor(std::ostream &os)
{
#if defined(LSOFT_POSIX)
    os << "\033[0m";
#elif defined(LSOFT_WINDOWS)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
#endif
}

void lsoft::log::Logger::printDateTime(std::ostream &os, uint32_t flags)
{
    // get time structures
    auto currentTime = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
    ::tm* ptrTm = localtime(&time);
    // buffer for write date/time
    char buffer[100];
    if( flags & Flag::DATE )
    {
        ::strftime(buffer, 100, "%Y-%m-%d", ptrTm);
        os << buffer << " ";
    }
    if( flags & Flag::TIME )
    {
        ::strftime(buffer, 100, "%H:%M:%S", ptrTm);
        os << buffer;
        if( flags & Flag::MILLISECONS )
        {
            int milliseconds = currentTime.time_since_epoch().count() / 1000000 % 1000;
            os << "." << std::setw(3) << std::setfill('0') << milliseconds << " ";
        }
        else
            os << " ";
    }
}

void lsoft::log::Logger::printThreadId(std::ostream &os)
{
    os << "[" << std::hex << std::this_thread::get_id() << "] ";
}
