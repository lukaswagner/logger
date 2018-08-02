#include "gtest/gtest.h"
#include "fixtures.hpp"
#include "logger.hpp"

TEST_F(File, CreatesOutput)
{
    logger::info() << "something";

    EXPECT_FALSE(fileOutput().empty());
}

TEST_F(File, SameAsConsole)
{
    logger::info() << "something";

    EXPECT_EQ(fileOutput(), coutOutput());
}

TEST_F(File, ContainsAllLevels)
{
    logger::info() << "text1";
    logger::warn() << "text2";

    const auto fileRegex = levelRegex("Inf") + levelRegex("Wrn");
    matchRegex(fileOutput(), fileRegex);
}
