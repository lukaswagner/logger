#pragma once

#include <string>
#include <memory>

#include "level.hpp"
#include "logger_export.hpp"

namespace logger
{
    class Line
    {
    public:
        // public interface

        LOGGER_EXPORT ~Line();
        Line LOGGER_EXPORT & operator <<(const std::string & string);

        // internal interface

        Line(const Level & level, std::string context);
        const Level & level() const;
        static std::string currentTimeString(const std::string & format);
        std::string string() const;

        // explicit defaults as requested by clang-tidy (cppcoreguidelines-special-member-functions)

        Line(const Line & line) = default;
        Line(Line&& line) = default;
        Line & operator=(const Line & line) = default;
        Line & operator=(Line && line) = default;

    private:
        Level m_level;
        std::string m_context;
        std::shared_ptr<std::ostringstream> m_stream;
    };
}
