/**
 * \brief Interfaces for logging and logger management
 * 
 * This header contains the main interfaces used for enabling/disabling/configuring the logger and for logging content.
 */

#pragma once

#include <string>

#include "line.hpp"
#include "logger_export.hpp"
#include "output.hpp"

namespace logger
{
    // public interface

    /**
     * \brief Checks if the logger is enabled.
     * \return True if the logger is enabled, false otherwise.
     */
    bool LOGGER_EXPORT enabled();
    /**
     * \brief Gets the minimum ::Level for console output.
     * \return The minumum ::Level for console output. Log messages with a lower ::Level won't be written to the console.
     */
    Level LOGGER_EXPORT consoleLevel();
    /**
    * \brief Gets the minimum ::Level for file output.
    * \return The minumum ::Level for file output. Log messages with a lower ::Level won't be written to the log file.
    */
    Level LOGGER_EXPORT fileLevel();
    /**
    * \brief Gets the output file for file logging.
    * \return The current output file, or an empty string if file logging is disabled.
    */
    std::string LOGGER_EXPORT logFile();

    /**
     * \brief Enables the logger with the given minimum \ref Level "Levels". Call again to change these settings. This results in a new log file being generated, if file logging is enabled.
     * \param consoleLevel Minimum ::Level for logging to console. Log messages with a lower ::Level won't be written to the console.
     * \param fileLevel Minimum ::Level for logging to file. Log messages with a lower ::Level won't be written to the log file.
     * \param logFileFormat Naming scheme for log files.
     */
    void LOGGER_EXPORT enable(const Level & consoleLevel = Info, const Level & fileLevel = Off, const std::string & logFileFormat = "log/%Y-%m-%d-%H-%M-%S.txt");
    /**
     * \brief Disables the logger.
     */
    void LOGGER_EXPORT disable();

    /**
     * \brief Gets the context lenght.
     * \return The context length. Contexts given to the message functions are adjusted to this number of characters.
     */
    int LOGGER_EXPORT contextLength();
    /**
     * \brief Sets the context lenght.
     * \param contextLength The context length. Contexts given to the message functions are adjusted to this number of characters.
     */
    void LOGGER_EXPORT setContextLength(const int & contextLength);
    /**
     * \brief Checks whether the current time is included in output.
     * \return True if the time is printed, false otherwise.
     */
    bool LOGGER_EXPORT printTime();
    /**
     * \brief Sets whether the current time should be included in output.
     * \param printTime True to print the time, false otherwise.
     */
    void LOGGER_EXPORT setPrintTime(const bool & printTime);
    /**
     * \brief Gets the format used printing the time.
     * \return The time format.
     */
    std::string LOGGER_EXPORT timeFormat();
    /**
    * \brief Sets the format used printing the time.
    * \return The time format, as described here: https://en.cppreference.com/w/cpp/io/manip/put_time
    */
    void LOGGER_EXPORT setTimeFormat(const std::string & timeFormat);

    /**
     * \brief Creates a new Line object with the ::Level ::Verbose. Once this object is destroyed, the content will be sent to the outputs. When logging to console, messages with this level will be sent to cout.
     * \param context The context in which the message is logged, allowing for more informative output. This could be the current function, for example.
     * \return A Line object, used for piping content.
     */
    Line LOGGER_EXPORT verbose(const std::string & context = "");
    /**
    * \brief Creates a new Line object with the ::Level ::Debug. Once this object is destroyed, the content will be sent to the outputs. When logging to console, messages with this level will be sent to cout.
    * \param context The context in which the message is logged, allowing for more informative output. This could be the current function, for example.
    * \return A Line object, used for piping content.
    */
    Line LOGGER_EXPORT debug(const std::string & context = "");
    /**
    * \brief Creates a new Line object with the ::Level ::Info. Once this object is destroyed, the content will be sent to the outputs. When logging to console, messages with this level will be sent to cout.
    * \param context The context in which the message is logged, allowing for more informative output. This could be the current function, for example.
    * \return A Line object, used for piping content.
    */
    Line LOGGER_EXPORT info(const std::string & context = "");
    /**
    * \brief Creates a new Line object with the ::Level ::Info. Once this object is destroyed, the content will be sent to the outputs. When logging to console, messages with this level will be sent to cerr.
    * \param context The context in which the message is logged, allowing for more informative output. This could be the current function, for example.
    * \return A Line object, used for piping content.
    */
    Line LOGGER_EXPORT warning(const std::string & context = "");
    /**
    * \brief Creates a new Line object with the ::Level ::Error. Once this object is destroyed, the content will be sent to the outputs. When logging to console, messages with this level will be sent to cerr.
    * \param context The context in which the message is logged, allowing for more informative output. This could be the current function, for example.
    * \return A Line object, used for piping content.
    */
    Line LOGGER_EXPORT error(const std::string & context = "");
}
