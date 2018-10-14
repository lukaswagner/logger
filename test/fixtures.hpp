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

struct IntValues
{
    unsigned long long m_input;
    std::string m_signedOutput;
    std::string m_unsignedOutput;
};

class DataTypes : public BaseFixture
{
public:
    template <class T> void checkDataType(T value, std::string string);
    template <class T> void checkInt();
private:
    std::map<int, IntValues> m_testValues =
    {
        std::pair<int, IntValues>(1, { 192u, "\xc0" , "\xc0" }),
        std::pair<int, IntValues>(2, { 60000u, "-5536", "60000" }),
        std::pair<int, IntValues>(4, { 4000000000u, "-294967296", "4000000000" }),
        std::pair<int, IntValues>(8, { 18000000000000000000u, "-446744073709551616", "18000000000000000000" })
    };
};

template <class T>
void DataTypes::checkDataType(T value, const std::string string)
{
    logger::info() << value;
    const auto coutRegex = contentRegex(string);
    matchRegex(coutOutput(), coutRegex);
}

template <class T>
void DataTypes::checkInt()
{
    auto values = m_testValues[sizeof(T)];
    T value = values.m_input;
    checkDataType(value, std::is_signed<T>() ? values.m_signedOutput : values.m_unsignedOutput);
}


class File : public BaseFixture
{
public:
    File();
};

class Macros : public BaseFixture
{
public:
    Macros();
};
