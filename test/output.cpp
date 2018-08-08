#include <regex>

#include "gtest/gtest.h"
#include "logger.hpp"
#include "fixtures.hpp"

TEST_F(Output, LevelTag)
{
    logger::verbose() << "text1";
    logger::debug() << "text2";
    logger::info() << "text3";
    logger::warning() << "text4";
    logger::error() << "text5";

    const auto coutRegex = levelRegex("Vrb") + levelRegex("Dbg") + levelRegex("Inf");
    matchRegex(coutOutput(), coutRegex);

    const auto cerrRegex = levelRegex("Wrn") + levelRegex("Err");
    matchRegex(cerrOutput(), cerrRegex);
}

TEST_F(Output, Time)
{
    logger::verbose() << "text1";

    const auto coutRegex = timeRegex(R"(\d\d:\d\d:\d\d)");
    matchRegex(coutOutput(), coutRegex);
}

TEST_F(Output, Context)
{
    logger::verbose("here") << "text1";
    logger::verbose("there") << "text2";

    const auto coutRegex = contextRegex("here      ")+ contextRegex("there     ");
    matchRegex(coutOutput(), coutRegex);
}

TEST_F(Output, Content)
{
    logger::verbose() << "text1";
    logger::verbose() << "text2";

    const auto coutRegex = contentRegex("text1") + contentRegex("text2");
    matchRegex(coutOutput(), coutRegex);
}

TEST_F(Output, BothStreams)
{
    logger::verbose() << "this is going into cout";
    logger::warning() << "this is going into cerr";

    const auto coutRegex = contentRegex(".*cout");
    matchRegex(coutOutput(), coutRegex);

    const auto cerrRegex = contentRegex(".*cerr");
    matchRegex(cerrOutput(), cerrRegex);
}
