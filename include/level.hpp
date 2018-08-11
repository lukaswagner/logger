#pragma once

#include <string>

namespace logger
{
    /**
     * \brief Levels for filtering messages based on importance.
     */
    enum Level
    {
        /**
         * \brief Used for low-level debugging information.
         */
        Verbose,
        /**
         * \brief Used for debugging information.
         */
        Debug,
        /**
         * \brief Used for important information.
         */
        Info,
        /**
         * \brief Used for logging non-critical problems.
         */
        Warning,
        /**
         * \brief Used for logging critical problems.
         */
        Error,
        /**
         * \brief Used for disabling outputs.
         */
        Off
    };

    static std::string getLogLevelLabel(const Level & level)
    {
        switch (level)
        {
        case Verbose:
            return "Vrb";
        case Debug:
            return "Dbg";
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
