#include "output.hpp"

#include <iostream>
#include <sstream>

#if defined(_WIN32)
#include <Windows.h>
#else
#include <sys/stat.h>
#endif

logger::Output::Output(const Level & consoleLevel, const Level & fileLevel, const std::string & logFileFormat)
    : m_consoleLevel(consoleLevel)
    , m_fileLevel(fileLevel)
    , m_stream(std::make_shared<std::ofstream>())
{
    if (fileLevel < Off)
    {
#if defined(_WIN32)
        CreateDirectory("log", nullptr);
#else
        mkdir("log", 0700);
#endif
        m_file = Line::currentTimeString(logFileFormat);
        m_stream->open(m_file, std::ios::out | std::ios::trunc);

        if(!m_stream->is_open())
        {
            std::cerr << "Could not open log file: " << m_file << std::endl;
            m_fileLevel = Off;
        }
    }
}

logger::Output::~Output()
{
    m_file = "";
    m_stream->close();
}

void logger::Output::write(const Line & line) const
{
    const auto string = line.string();

    if(line.level() >= m_consoleLevel)
    {
        (line.level() >= Warning ? std::cerr : std::cout) << string << std::endl;
    }

    if(line.level() >= m_fileLevel)
    {
        *m_stream << string << std::endl;
        m_stream->flush();
    }
}

logger::Level logger::Output::consoleLevel() const
{
    return m_consoleLevel;
}

logger::Level logger::Output::fileLevel() const
{
    return m_fileLevel;
}

std::string logger::Output::file() const
{
    return m_file;
}
