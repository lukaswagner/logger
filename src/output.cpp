#include "../include/output.hpp"

#include <iostream>
#include <sstream>

#if defined(_WIN32)
#include <Windows.h>
#else
#include <sys/stat.h>
#endif

logger::Output::Output(const Level & consoleLevel, const Level & fileLevel)
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
        m_stream->open(Line::currentTimeString("log/%Y-%m-%d-%H-%M-%S.txt"), std::ios::out | std::ios::trunc);

        if(!m_stream->is_open())
        {
            std::cout << "Could not open log file." << std::endl;
            m_fileLevel = Off;
        }
    }
}

logger::Output::~Output()
{
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
