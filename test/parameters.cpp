#include "gtest/gtest.h"
#include "logger.hpp"
#include "fixtures.hpp"

TEST_F(Parameter, ContextLength)
{
    EXPECT_EQ(m_defaultContextLength, 10);

    logger::info("normal") << "that's a normal sized context";

    EXPECT_NO_THROW(logger::setContextLength(1));
    EXPECT_EQ(logger::contextLength(), 1);

    logger::info("short") << "the context is already short but will be cut even shorter";

    EXPECT_NO_THROW(logger::setContextLength(20));
    EXPECT_EQ(logger::contextLength(), 20);

    logger::info("a very long context") << "sometimes you need more space";

    const auto coutRegex = contextRegex("normal    ") + contextRegex("s") + contextRegex("a very long context ");
    matchRegex(coutOutput(), coutRegex);
}

TEST_F(Parameter, PrintTime)
{
    EXPECT_TRUE(m_defaultPrintTime);

    logger::info() << "text1";

    EXPECT_NO_THROW(logger::setPrintTime(false));
    EXPECT_FALSE(logger::printTime());

    logger::info() << "text2";

    const auto coutRegex = timeRegex() + noTimeRegex();
    matchRegex(coutOutput(), coutRegex);
}

TEST_F(Parameter, TimeFormat)
{
    EXPECT_EQ(m_defaultTimeFormat, "%H:%M:%S");

    logger::info() << "text1";

    EXPECT_NO_THROW(logger::setTimeFormat("%H hours and %M minutes"));
    EXPECT_EQ(logger::timeFormat(), "%H hours and %M minutes");

    logger::info() << "text2";

    const auto coutRegex = timeRegex() + timeRegex(R"(\d\d hours and \d\d minutes)");
    matchRegex(coutOutput(), coutRegex);
}

TEST_F(Parameter, Level)
{
    EXPECT_EQ(logger::consoleLevel(), logger::Info);

    logger::info() << "this should be visible";
    logger::debug() << "this should be hidden";
    logger::info() << "and visible again";

    EXPECT_NO_THROW(logger::enable(logger::Debug));

    logger::debug() << "and this should be visible";

    const auto coutRegex = levelRegex("Inf") + levelRegex("Inf") + levelRegex("Dbg");
    matchRegex(coutOutput(), coutRegex);
}
