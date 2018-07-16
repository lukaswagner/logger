#pragma once

#include <memory>

#include "output.hpp"

namespace logger
{
    // global vars

    extern bool g_enabled;
    extern int g_contextLength;
    extern bool g_printTime;
    extern std::string g_timeFormat;
    extern std::shared_ptr<Output> g_output;
}
