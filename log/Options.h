#ifndef LSOFT_LOG_OPTIONS_H
#define LSOFT_LOG_OPTIONS_H

#include "common/NoCopyable.h"

#include <ostream>
#include <fstream>

namespace lsoft {
namespace log {

namespace Flag {
enum
{
    DATE = 0x01,
    TIME = 0x02,
    DATETIME = DATE | TIME,
    NAME = 0x04,
    THREAD = 0x08,
    TYPE = 0x10,
    MILLISECONS = 0x20,
    COLOR = 0x40,
    SEPARATION = DATETIME | NAME | THREAD | TYPE,
    DEFAULT = TIME | TYPE | NAME
};
}

enum class Type
{
    TRACE=0,
    SEGMENT=1,
    DEBUG=2,
    INFO=3,
    WARNING=4,
    ERROR=5,
    CRITICAL=6
};

/*
 * Options
 * Event logging options
 *
 */

class Options: public NoCopyable
{
public:

    static Options& instance();

    // level logging
    void setLowType(Type type);
    Type lowType() const;

    // input / output stream
    void setOutput(std::ostream& output);
    void setOutput(std::ostream& output, std::ostream& error);
    void setOutputError(std::ostream& error);
    std::ostream& output();
    std::ostream& error();

    // settings of information to output
    void addFlag(uint32_t flag);
    void removeFlag(uint32_t flag);
    void setFlags(uint32_t flags);
    uint32_t flags();

    // redirect to file log output/error
    bool redirectToFile(const std::string& filename, bool append=true);      // output and error
    bool redirectErrorToFile(const std::string& filename, bool append=true); // only error

private:
    Options();

    Type _lowType;
    uint32_t _flags;
    std::ofstream _outputFile, _errorFile;
    std::ostream* _output;
    std::ostream* _error;
};

}} // namespace lsoft::log

#endif // LSOFT_LOG_OPTIONS_H
