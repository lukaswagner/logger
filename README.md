# logger
Multi-level logger for C++. Supports logging to both console and file. Based on logger from [cginternals/cppassist](https://github.com/cginternals/cppassist).

## Contents

1. [Setup](#setup)
    1. [Basic Dependencies](#basic-dependencies)
    2. [Dependency Setup](#dependency-setup)
    3. [Building the Project](#building-the-project)
2. [Usage](#usage)
    1. [Enabling the Logger](#enabling-the-logger)
    2. [Creating Output](#creating-output)
    3. [Further Customization](#further-customization)
    4. [Complete Example](#complete-example)
3. [Build Status](#build-status)

## Setup

### Basic Dependencies

You'll need
* [CMake](https://cmake.org/) to generate build files.
* A C++14-compatible compiler, e.g. g++7 or VS 2017.
* [Git](https://git-scm.com/) to automatically clone googletest.
* [Doxygen](http://www.doxygen.org/) if you want to generate the documentation.

### Dependency Setup

tl;dr:
```sh
cd dependencies
cmake .
```

The tests use the [googletest framework](https://github.com/google/googletest), so you'll have to download and build this if you want to build the tests. In order to do so, just run `cmake .` in the dependecy subdirectory. This will build googletest with the default generator. Hint for VS users: By default, a 32 bit compiler is used. You should specify the correct generator, for example by calling `cmake . -G "Visual Studio 15 2017 Win64"`.

If you already have a compiled version of googletest lying around, you can skip this and just specify the installation's base dir by passing `-DGTEST_ROOT="path/to/gtest"` when configuring the logger.

### Building the Project

tl;dr:
```sh
mkdir build
cd build
cmake .. -DBUILD_EXAMPLE=ON -DBUILD_TESTS=ON -DBUILD_DOCS=ON
```

Create a build dir and configure the project using CMake. There are three options to enable optional targets:  
* BUILD_EXAMPLE: Builds an example application using the logger.
* BUILD_TESTS: Builds the tests checking the logger's functionality. Requires googletest.
* BUILD_DOCS: Generates the documentation. Requires Doxygen.

Afterwards, you can build the project. Just open the `.sln` in Visual Studio and build it from there, or use `make` if you're on Unix/Linux. Note: The docs are not included in the default target, you'll have to explicitly build them.

## Usage

### Enabling the Logger

Enable the logger by calling `enable()` with the appropriate levels. Let's say you want to show only the important logs in the console to maintain a cleaner output, but write all messages to the file in case you need to debug your application:
```cpp
logger::enable(logger::Info, logger::Verbose);
```
Only messages with the level Info or higher will be visible in the console, while everything (Verbose is the lowest level) will be written to the log file when setting up the logger like this.

### Creating Output

Use the functions resembling the log levels to obtain a line object. You can use this to pipe content as if it were a std::ostream.
```cpp
logger::info() << "a string: " << anInt;
```
Once the line object gets destroyed, all content piped into it is concatenated with the message header and sent to the outputs.

Note: Message with the levels Verbose, Debug and Info are sent to `stdout`, while message with the levels Warning and Error are sent to `stderr`.

Since the `<<` operator is implemented using a template, you can print everything you can send to an ostream. If you provide your own `std::ostream& operator<<` overload, you can even print your custom classes (see example.cpp for an example).

Additionally, you can pass a context to the log functions. You can use this to provide a better structured output. For example, calling
```cpp
logger::info("Main setup") << "Reading config file..."
```
results in the following output:
```
[Inf] [19:29:34] Main setup: Reading config file...
```

### Further Customization

By default, contexts are fixed to 10 characters, resulting in the output being aligned cleanly. In order to change this number of characters according to your needs, you can use `setContextLength()`:
```cpp
logger::info("A very long context") << "It's cut off.";
logger::setContextLength(20);
logger::info("A very long context") << "Now it fits."
```
Output:
```
[Inf] [19:37:10] A very lon: It's cut off.
[Inf] [19:37:10] A very long context : Now it fits.
```

You can customize the time output by using `setTimeFormat()` (see [std::put_time](https://en.cppreference.com/w/cpp/io/manip/put_time) for the used syntax) or completely hide it by using `setPrintTime()`:
```cpp
logger::info("Time test") << "Default time format is %H:%M:%S.";
logger::setTimeFormat("%H:%M");
logger::info("Time test") << "Now the seconds are hidden.";
logger::setPrintTime(false);
logger::info("Time test") << "And now the time is omitted.";
```
Output:
```
[Inf] [19:47:26] Time test : Default time format is %H:%M:%S.
[Inf] [19:47] Time test : Now the seconds are hidden.
[Inf] Time test : And now the time is omitted.
```
The same time syntax is used for naming the generated log file. By default, `log/%Y-%m-%d-%H-%M-%S.txt` is used - resulting in a file like `2018-08-11-20-00-10.txt` being created in the subdirectory `log`. You can customize this by passing a string cointaining the desired format to `enable()`.

### Complete Example

This example is take from the example application.

```cpp
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
```
`stdout` output:
```
[Inf] Setup          : Loading config...
[Inf] Setup          : Successfully loaded config.
```
`stderr` output:
```
[Wrn] [19:25:48] Input parsing  : Invalid input - The custom object contains the value 1338
```

## Build Status
| Branch | [Linux](https://travis-ci.com/lukaswagner/logger)                           | [Windows](https://ci.appveyor.com/project/lukaswagner/logger/branch/master)                          |
|--------|-----------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------|
| master | ![Build Status](https://travis-ci.com/lukaswagner/logger.svg?branch=master) | ![Build status](https://ci.appveyor.com/api/projects/status/lvb82mnhslxd65k6/branch/master?svg=true) |
