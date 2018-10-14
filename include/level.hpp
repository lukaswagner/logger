/**\file level.hpp
 * \brief Log levels
 * 
 * This header contains the available log levels for filtering log messages.
 */

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
         * \brief Used for low-level debugging information. When logging to console, messages with this level will be sent to cout.
         */
        Verbose,
        /**
         * \brief Used for debugging information. When logging to console, messages with this level will be sent to cout.
         */
        Debug,
        /**
         * \brief Used for important information. When logging to console, messages with this level will be sent to cout.
         */
        Info,
        /**
         * \brief Used for logging non-critical problems. When logging to console, messages with this level will be sent to cerr.
         */
        Warning,
        /**
         * \brief Used for logging critical problems. When logging to console, messages with this level will be sent to cerr.
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
