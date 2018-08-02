#include "fixtures.hpp"

#include <iostream>
#include <regex>
#include <cstdio>

#include "logger.hpp"

BaseFixture::BaseFixture(const logger::Level consoleLevel, const logger::Level fileLevel)
{
    // switch out cout/cerr in order to check logging output
    m_coutBuf = std::cout.rdbuf(m_cout.rdbuf());
    m_cerrBuf = std::cerr.rdbuf(m_cerr.rdbuf());

    enable(consoleLevel, fileLevel);
}

BaseFixture::~BaseFixture()
{
    // switch streams back
    std::cout.rdbuf(m_coutBuf);
    std::cerr.rdbuf(m_cerrBuf);

    // store values which will be unavailable once logger is disabled
    const auto fileOutputEnabled = logger::fileLevel() < logger::Off;
    const auto file = logger::logFile();

    logger::disable();

    // clean up og file after logger is disabled
    if(fileOutputEnabled)
    {
        remove(file.c_str());
    }
}

std::string BaseFixture::coutOutput() const
{
    return m_cout.str();
}

std::string BaseFixture::cerrOutput() const
{
    return m_cerr.str();
}

std::string BaseFixture::fileOutput()
{
    // make sure that logging to file is enabled
    if(logger::fileLevel() == logger::Off)
    {
        return "";
    }

    // store state of file
    const auto consoleLevel = logger::consoleLevel();
    const auto fileLevel = logger::fileLevel();
    const auto logFile = logger::logFile();

    // need to close file before reading it
    logger::disable();

    // read output
    auto in = std::ifstream(logFile);
    EXPECT_TRUE(in.is_open());
    auto string = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    in.close();

    // clean up log file since it won't be removed by destructor
    remove(logFile.c_str());

    // restart logger in case we want to test something else
    enable(consoleLevel, fileLevel);

    return string;
}

std::string BaseFixture::levelRegex(const std::string& tag)
{
    return lineRegex(tag);
}

std::string BaseFixture::timeRegex(const std::string& time)
{
    return lineRegex(".{3}", time);
}

std::string BaseFixture::contextRegex(const std::string& context)
{
    return lineRegex(".{3}", ".*", context);
}

std::string BaseFixture::contentRegex(const std::string& content)
{
    return lineRegex(".{3}", ".*", ".*", content);
}

std::string BaseFixture::noTimeRegex()
{
    return R"(\[.{3}\] .*: .*(\r\n|\r|\n))";
}

void BaseFixture::matchRegex(const std::string& string, const std::string& regex)
{
    EXPECT_TRUE(std::regex_match(string, std::regex(regex))) << 
        "Could not match regex. String:" << std::endl <<
        ">>>" << string << "<<<" << std::endl <<
        "Regex:" << std::endl <<
        ">>>" << regex << "<<<" << std::endl;
}

std::string BaseFixture::lineRegex(const std::string& tag, const std::string& time, const std::string& context, const std::string& message)
{
    return R"(\[)" + tag + R"(\] \[)" + time + R"(\] )" + context + ": " + message + R"((\r\n|\r|\n))";
}

Output::Output() : BaseFixture(logger::Verbose, logger::Off) { }

Parameter::Parameter()
    : BaseFixture()
    , m_defaultContextLength(logger::contextLength())
    , m_defaultPrintTime(logger::printTime())
    , m_defaultTimeFormat(logger::timeFormat()) { }

Parameter::~Parameter()
{
    logger::setContextLength(m_defaultContextLength);
    logger::setPrintTime(m_defaultPrintTime);
    logger::setTimeFormat(m_defaultTimeFormat);
}

File::File() : BaseFixture(logger::Info, logger::Info) { }
