#include "gtest/gtest.h"
#include "fixtures.hpp"

TEST_F(DataTypes, String)
{
    const std::string value = "a string";
    checkDataType(value, value);
}

TEST_F(DataTypes, CString)
{
    const char* value = "a string";
    checkDataType(value, value);
}

TEST_F(DataTypes, Bool)
{
    const bool value = true;
    checkDataType(value, "1");
}

TEST_F(DataTypes, Char)
{
    const char value = 0xc0;
    checkDataType(value, "\xc0");
}

TEST_F(DataTypes, UnsignedChar)
{
    const unsigned char value = 0xc0;
    checkDataType(value, "\xc0");
}

TEST_F(DataTypes, Int)
{
    const int value = 4000000000;
    checkDataType(value, "-294967296");
}

TEST_F(DataTypes, UnsignedInt)
{
    const unsigned int value = 4000000000;
    checkDataType(value, "4000000000");
}

TEST_F(DataTypes, ShortInt)
{
    const short int value = 40000;
    checkDataType(value, "-25536");
}

TEST_F(DataTypes, UnsignedShortInt)
{
    const unsigned short int value = 40000;
    checkDataType(value, "40000");
}

TEST_F(DataTypes, LongInt)
{
    const long int value = 4000000000;
    checkDataType(value, "-294967296");
}

TEST_F(DataTypes, UnsignedLongInt)
{
    const unsigned long int value = 4000000000;
    checkDataType(value, "4000000000");
}

TEST_F(DataTypes, LongLongInt)
{
    const long long int value = 18000000000000000000;
    checkDataType(value, "-446744073709551616");
}

TEST_F(DataTypes, UnsignedLongLongInt)
{
    const unsigned long long int value = 18000000000000000000;
    checkDataType(value, "18000000000000000000");
}

TEST_F(DataTypes, Float)
{
    const float value = 1.28;
    checkDataType(value, "1.28");
}

TEST_F(DataTypes, Double)
{
    const double value = 1.28;
    checkDataType(value, "1.28");
}

TEST_F(DataTypes, LongDouble)
{
    const long double value = 1.28;
    checkDataType(value, "1.28");
}

TEST_F(DataTypes, StreamManipulators)
{
    const bool value = true;
    logger::info() << std::boolalpha << value << " " << std::noboolalpha << value;
    const auto coutRegex = contentRegex("true 1");
    matchRegex(coutOutput(), coutRegex);
}
