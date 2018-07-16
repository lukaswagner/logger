#pragma once

#include <string>

#include "line.hpp"
#include "logger_export.hpp"
#include "output.hpp"

namespace logger
{
    // public interface

    void LOGGER_EXPORT enable(const Level & consoleLevel = Info, const Level & fileLevel = Off);
    void LOGGER_EXPORT disable();

    int LOGGER_EXPORT contextLength();
    void LOGGER_EXPORT setContextLength(const int & contextLength);
    bool LOGGER_EXPORT printTime();
    void LOGGER_EXPORT setPrintTime(const bool & printTime);
    std::string LOGGER_EXPORT timeFormat();
    void LOGGER_EXPORT setTimeFormat(const std::string & timeFormat);

    Line LOGGER_EXPORT verbose(const std::string & context = "");
    Line LOGGER_EXPORT debug(const std::string & context = "");
    Line LOGGER_EXPORT info(const std::string & context = "");
    Line LOGGER_EXPORT warn(const std::string & context = "");
    Line LOGGER_EXPORT error(const std::string & context = "");
}
