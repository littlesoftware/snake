#include "Options.h"

#include <iostream>

lsoft::log::Options &lsoft::log::Options::instance()
{
    static Options options;
    return options;
}

void lsoft::log::Options::setLowType(Type type)
{
    _lowType = type;
}

lsoft::log::Type lsoft::log::Options::lowType() const
{
    return _lowType;
}

void lsoft::log::Options::setOutput(std::ostream &output)
{
    _output = &output;
}

void lsoft::log::Options::setOutput(std::ostream &output, std::ostream &error)
{
    _output = &output;
    _error = &error;
}

void lsoft::log::Options::setOutputError(std::ostream &error)
{
    _error = &error;
}

std::ostream &lsoft::log::Options::output()
{
    return *_output;
}

std::ostream &lsoft::log::Options::error()
{
    return *_error;
}

void lsoft::log::Options::addFlag(uint32_t flag)
{
    _flags |= flag;
}

void lsoft::log::Options::removeFlag(uint32_t flag)
{
    _flags &= ~flag;
}

void lsoft::log::Options::setFlags(uint32_t flags)
{
    _flags = flags;
}

uint32_t lsoft::log::Options::flags()
{
    return _flags;
}

bool lsoft::log::Options::redirectToFile(const std::string &filename, bool append)
{
    _outputFile.open( filename, std::ios_base::out | (append?std::ios_base::app:std::ios_base::trunc) );
    if( !_outputFile.is_open() )
        return false;
    setOutput(_outputFile, _outputFile);
    return true;
}

bool lsoft::log::Options::redirectErrorToFile(const std::string &filename, bool append)
{
    _errorFile.open( filename, std::ios_base::out | (append?std::ios_base::app:std::ios_base::trunc) );
    if( !_errorFile.is_open() )
        return false;
    setOutputError(_errorFile);
    return true;
}

lsoft::log::Options::Options():
    _lowType(Type::DEBUG),
    _flags(Flag::DEFAULT),
    _output(&std::cout),
    _error(&std::cerr)
{
}
