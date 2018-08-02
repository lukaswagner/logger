#pragma once

#include <fstream>
#include <memory>

#include "level.hpp"
#include "line.hpp"

namespace logger
{
    class Output
    {
    public:
        // internal interface

        Output(const Level & consoleLevel, const Level & fileLevel, const std::string & logFileFormat);
        ~Output();
        void write(const Line & line) const;

        Level consoleLevel() const;
        Level fileLevel() const;
        std::string file() const;

        // explicit defaults as requested by clang-tidy (cppcoreguidelines-special-member-functions)

        Output(const Output & line) = default;
        Output(Output&& line) = default;
        Output & operator=(const Output & line) = default;
        Output & operator=(Output && line) = default;

    private:
        Level m_consoleLevel;
        Level m_fileLevel;
        std::string m_file;
        std::shared_ptr<std::ofstream> m_stream;
    };
}
