#include "logger.hpp"

// create a custom class to showcase operator overloading
class CustomClass
{
public:
    int m_memberVar;
};

// implement an operator for piping the class to an ostream - this will allow usage with the logger as well
std::ostream& operator<<(std::ostream& stream, const CustomClass& object)
{
    return stream << "The custom object contains the value " << object.m_memberVar;
}

int main(int argc, char* argv[])
{
    // enable the logger, only show messages with level >= Info and disable file output completely
    logger::enable(logger::Info, logger::Off);

    // let's disable the time output during the setup
    logger::setPrintTime(false);

    // we'll be using a long context name - let's increase the context length
    logger::setContextLength(15);

    // this will be shown
    logger::info("Setup") << "Loading config...";

    // load some file, iterate over inputs, whatever - let's pretend this block is called in a loop
    {
        const auto someIntInConfig = 17;
        // this will be hidden in output, since Debug < Info
        logger::debug("Setup") << "Found value " << someIntInConfig << " in config.";
    }

    // this will be shown again
    logger::info("Setup") << "Successfully loaded config.";

    // now we're re-enabling time output
    logger::setPrintTime(true);

    // by parsing some input we created this custom object
    const auto customObject = CustomClass{ 1338 };

    // warnings and errors are redirected to cerr instead of cout
    if (customObject.m_memberVar > 1337)
        logger::warning("Input parsing") << "Invalid input - " << customObject;
}
