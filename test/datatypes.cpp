#include "gtest/gtest.h"
#include "fixtures.hpp"
#include "logger.hpp"

TEST_F(DataTypes, String)
{
    logger::info() << "a string";

    const auto coutRegex = contentRegex("a string");
    matchRegex(coutOutput(), coutRegex);
}
