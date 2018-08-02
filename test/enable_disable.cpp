#include <iostream>
#include <sstream>
#include <cstdio>

#include "gtest/gtest.h"
#include "logger.hpp"
#include "fixtures.hpp"

// enabling / disabling the logger

TEST(EnableAndDisable, Default)
{
    EXPECT_NO_THROW(logger::enable());
    EXPECT_TRUE(logger::enabled());
    EXPECT_EQ(logger::consoleLevel(), logger::Info);
    EXPECT_EQ(logger::fileLevel(), logger::Off);

    EXPECT_NO_THROW(logger::disable());
    EXPECT_FALSE(logger::enabled());
}

TEST(EnableAndDisable, ConsoleLevel)
{
    EXPECT_NO_THROW(logger::enable(logger::Debug));
    EXPECT_TRUE(logger::enabled());
    EXPECT_EQ(logger::consoleLevel(), logger::Debug);
    EXPECT_EQ(logger::fileLevel(), logger::Off);

    EXPECT_NO_THROW(logger::disable());
    EXPECT_FALSE(logger::enabled());
}

TEST(EnableAndDisable, FileLevel)
{
    EXPECT_NO_THROW(logger::enable(logger::Info, logger::Info));
    EXPECT_TRUE(logger::enabled());
    EXPECT_EQ(logger::consoleLevel(), logger::Info);
    EXPECT_EQ(logger::fileLevel(), logger::Info);

    auto file = logger::logFile();

    EXPECT_NO_THROW(logger::disable());
    EXPECT_FALSE(logger::enabled());

    remove(file.c_str());
}

TEST(EnableAndDisable, CatchFileError)
{
    // replace cerr buffer to hide expected error
    auto cerr = std::ostringstream();
    const auto buf = std::cerr.rdbuf(cerr.rdbuf());

    EXPECT_NO_THROW(logger::enable(logger::Info, logger::Info, ""));
    EXPECT_TRUE(logger::enabled());
    EXPECT_EQ(logger::consoleLevel(), logger::Info);
    EXPECT_EQ(logger::fileLevel(), logger::Off);

    EXPECT_NO_THROW(logger::disable());
    EXPECT_FALSE(logger::enabled());

    std::cerr.rdbuf(buf);
}
