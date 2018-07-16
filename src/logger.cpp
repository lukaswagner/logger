#include "../include/logger.hpp"

#include "../include/globals.hpp"

void logger::enable(const Level & consoleLevel, const Level & fileLevel)
{
    g_output = std::make_shared<Output>(consoleLevel, fileLevel);
    g_enabled = true;
}

void logger::disable()
{
    g_output.reset();
    g_enabled = false;
}

int logger::contextLength()
{
    return g_contextLength;
}

void logger::setContextLength(const int & contextLength)
{
    g_contextLength = contextLength;
}

bool logger::printTime()
{
    return g_printTime;
}

void logger::setPrintTime(const bool & printTime)
{
    g_printTime = printTime;
}

std::string logger::timeFormat()
{
    return g_timeFormat;
}

void logger::setTimeFormat(const std::string & timeFormat)
{
    g_timeFormat = timeFormat;
}

logger::Line logger::verbose(const std::string & context)
{
    return Line(Verbose, context);
}

logger::Line logger::debug(const std::string & context)
{
    return Line(Debug, context);
}

logger::Line logger::info(const std::string & context)
{
    return Line(Info, context);
}

logger::Line logger::warn(const std::string & context)
{
    return Line(Warning, context);
}

logger::Line logger::error(const std::string & context)
{
    return Line(Error, context);
}
