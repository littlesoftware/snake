#include "Options.h"

#include <iostream>

lsoft::log::Options &lsoft::log::Options::instance()
{
    static Options options;
    return options;
}

void lsoft::log::Options::setLowType(Type type)
{
    m_lowType = type;
}

lsoft::log::Type lsoft::log::Options::lowType() const
{
    return m_lowType;
}

void lsoft::log::Options::setOutput(std::ostream &output)
{
    m_output = &output;
}

void lsoft::log::Options::setOutput(std::ostream &output, std::ostream &error)
{
    m_output = &output;
    m_error = &error;
}

void lsoft::log::Options::setOutputError(std::ostream &error)
{
    m_error = &error;
}

std::ostream &lsoft::log::Options::output()
{
    return *m_output;
}

std::ostream &lsoft::log::Options::error()
{
    return *m_error;
}

void lsoft::log::Options::addFlag(uint32_t flag)
{
    m_flags |= flag;
}

void lsoft::log::Options::removeFlag(uint32_t flag)
{
    m_flags &= ~flag;
}

void lsoft::log::Options::setFlags(uint32_t flags)
{
    m_flags = flags;
}

uint32_t lsoft::log::Options::flags()
{
    return m_flags;
}

bool lsoft::log::Options::redirectToFile(const std::string &filename, bool append)
{
    m_outputFile.open( filename, std::ios_base::out | (append?std::ios_base::app:std::ios_base::trunc) );
    if( !m_outputFile.is_open() )
        return false;
    setOutput(m_outputFile, m_outputFile);
    return true;
}

bool lsoft::log::Options::redirectErrorToFile(const std::string &filename, bool append)
{
    m_errorFile.open( filename, std::ios_base::out | (append?std::ios_base::app:std::ios_base::trunc) );
    if( !m_errorFile.is_open() )
        return false;
    setOutputError(m_errorFile);
    return true;
}

lsoft::log::Options::Options():
    m_lowType(Type::DEBUG),
    m_flags(Flag::DEFAULT),
    m_output(&std::cout),
    m_error(&std::cerr)
{
}
