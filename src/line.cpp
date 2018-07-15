#include "../include/line.hpp"

#include <sstream>
#include <utility>
#include <ctime>

#include "../include/logger.hpp"
#include <iomanip>

logger::Line::Line(const Level & level, std::string context)
    : m_level(level)
    , m_context(std::move(context))
    , m_stream(std::make_shared<std::ostringstream>())
{
    m_context.resize(g_contextLength, ' ');
}

logger::Line::~Line()
{
    g_output->write(*this);
}

logger::Line & logger::Line::operator<<(const std::string & string)
{
    *m_stream << string;
    return *this;
}

const logger::Level & logger::Line::level() const
{
    return m_level;
}

std::string logger::Line::currentTimeString(const std::string & format)
{
    auto oss = std::ostringstream();
    auto time = std::time(nullptr);
    auto local = tm();

    // localtime is marked as deprecated in VS, the VS-only localtime_s is preferred
#ifdef _MSC_VER
    localtime_s(&local, &time);
#else
    local = *std::localtime(&time);
#endif

    oss << std::put_time(&local, format.c_str());
    return oss.str();
}

std::string logger::Line::string() const
{
    auto oss = std::ostringstream();
    oss << "[" << getLogLevelLabel(m_level) << "] ";
    if(g_printTime)
    {
        oss << "[" << currentTimeString(g_timeFormat) << "] ";
    }
    oss << m_context << ": " << m_stream->str();

    return oss.str();
}
