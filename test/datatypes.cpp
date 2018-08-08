#include "gtest/gtest.h"
#include "fixtures.hpp"

#define TYPE_TEST(name, type, input, output) TEST_F(DataTypes, name){ const type value = input; checkDataType(value, output); }
TYPE_TEST(String, std::string, "a string", "a string")
TYPE_TEST(CString, char*, "a string", "a string")
TYPE_TEST(Bool, bool, true, "1")
TYPE_TEST(Float, float, 1.28, "1.28")
TYPE_TEST(Double, double, 1.28, "1.28")
TYPE_TEST(LongDouble, long double, 1.28, "1.28")

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

TYPE_TEST(CustomClass, CustomClass, CustomClass(), "This is a custom stream output operator.")
