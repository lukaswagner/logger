#include "fixtures.hpp"

#include "macros.hpp"

TEST_F(Macros, DEBUG_EXPR_LogCurrentFile)
{
    DEBUG_EXPR(const auto string = "assigning a string";)

    // check against the hard-coded file
    const auto regex = contentRegex(R"(.*\(.*macros\.cpp:.*\))");
    matchRegex(coutOutput(), regex);
}

TEST_F(Macros, DEBUG_EXPR_LogCurrentLine)
{
    DEBUG_EXPR(const auto string = "assigning a string";)

    // check against the hard-coded line
    const auto regex = contentRegex(R"(.*\(.*:16\))");
    matchRegex(coutOutput(), regex);
}

TEST_F(Macros, DEBUG_EXPR_LogExpression)
{
    DEBUG_EXPR(const auto string = "assigning a string";)

    const auto regex = contentRegex(R"(const auto string = "assigning a string"; \(.*\))");
    matchRegex(coutOutput(), regex);
}

TEST_F(Macros, DEBUG_EXPR_ExecuteExpression)
{
    DEBUG_EXPR(const auto string = "assigning a string";)

    EXPECT_STREQ(string, "assigning a string");
}

TEST_F(Macros, DEBUG_EXPR_SemicolonInMacro)
{
    DEBUG_EXPR(const auto string = "assigning a string";)
}

TEST_F(Macros, DEBUG_EXPR_SemicolonAfterMacro)
{
    DEBUG_EXPR(const auto string = "assigning a string");
}

TEST_F(Macros, DEBUG_EXPR_SemicolonInAndAfterMacro)
{
    DEBUG_EXPR(const auto string = "assigning a string";);
}

TEST_F(Macros, DEBUG_EXPR_NoSemicolon)
{
    DEBUG_EXPR(const auto string = "assigning a string")
}

TEST_F(Macros, DEBUG_VAL_LogLiteral)
{
    DEBUG_VAL(42)

    const auto regex = contentRegex(R"(42 = 42)");
    matchRegex(coutOutput(), regex);
}

TEST_F(Macros, DEBUG_VAL_LogVariable)
{
    const auto a = 42;
    DEBUG_VAL(a)

    const auto regex = contentRegex(R"(a = 42)");
    matchRegex(coutOutput(), regex);
}

TEST_F(Macros, DEBUG_VAL_LogExpression)
{
    DEBUG_VAL(6 * 7)

    const auto regex = contentRegex(R"(6 \* 7 = 42)");
    matchRegex(coutOutput(), regex);
}

TEST_F(Macros, DEBUG_VAL_SemicolonAfterMacro)
{
    DEBUG_VAL(6 * 7);
}

TEST_F(Macros, DEBUG_VAL_NoSemicolon)
{
    DEBUG_VAL(6 * 7)
}
