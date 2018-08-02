#include "logger.hpp"

int main(int argc, char* argv[])
{
    enable(logger::Info, logger::Info);
    logger::info("test") << "something " << "something else";
}
