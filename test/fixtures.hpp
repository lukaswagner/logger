#pragma once

#include <sstream>
#include <streambuf>
#include <gtest/gtest.h>

#include "level.hpp"
#include "logger.hpp"

void removeLogFile(const std::string& file);

class BaseFixture : public testing::Test
{
public:
    explicit BaseFixture(logger::Level consoleLevel = logger::Info, logger::Level fileLevel = logger::Off);
    ~BaseFixture();
    std::string coutOutput() const;
    std::string cerrOutput() const;
    static std::string fileOutput();
    static std::string levelRegex(const std::string& tag = ".{3}");
    static std::string timeRegex(const std::string& time = R"(\d\d:\d\d:\d\d)");
    static std::string contextRegex(const std::string& context = ".{10}");
    static std::string contentRegex(const std::string& content = ".*");
    static std::string noTimeRegex();
    static void matchRegex(const std::string& string, const std::string& regex);

private:
    static std::string lineRegex(const std::string& tag = ".{3}", const std::string& time = ".*", const std::string& context = ".*", const std::string& message = ".*");
    std::ostringstream m_cout;
    std::ostringstream m_cerr;
    std::streambuf* m_coutBuf;
    std::streambuf* m_cerrBuf;
};

class Output : public BaseFixture
{
public:
    Output();
};

class Parameter : public BaseFixture
{
public:
    Parameter();
    ~Parameter();
protected:
    int m_defaultContextLength;
    bool m_defaultPrintTime;
    std::string m_defaultTimeFormat;
};

class DataTypes : public BaseFixture { };

class File : public BaseFixture
{
public:
    File();
};
