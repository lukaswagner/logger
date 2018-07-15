#pragma once

#include <string>

namespace logger
{
    enum Level
    {
        Verbose,
        Debug,
        Info,
        Warning,
        Error,
        Off
    };

    static std::string getLogLevelLabel(const Level & level)
    {
        switch (level)
        {
        case Verbose:
            return "Vrb";
        case Debug:
            return "Deb";
        case Info:
            return "Inf";
        case Warning:
            return "Wrn";
        case Error:
            return "Err";
        case Off:
        default:
            return "";
        }
    }
}
