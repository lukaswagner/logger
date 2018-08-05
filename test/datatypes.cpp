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

#define INT_TEST(name, type) TEST_F(DataTypes, name){ checkInt<type>(); }
INT_TEST(Char, char)
INT_TEST(UnsignedChar, unsigned char)
INT_TEST(Short, short)
INT_TEST(UnsignedShort, unsigned short)
INT_TEST(Int, int)
INT_TEST(UnsignedInt, unsigned int)
INT_TEST(Long, long)
INT_TEST(UnsignedLong, unsigned long)
INT_TEST(LongLong, long long)
INT_TEST(UnsignedLongLong, unsigned long long)

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

class CustomClass { };

std::ostream& operator<<(std::ostream& stream, const CustomClass& object)
{
    return stream << "This is a custom stream output operator.";
}

TEST_F(DataTypes, CustomClass)
{
    const CustomClass value = CustomClass();
    checkDataType(value, "This is a custom stream output operator.");
}
