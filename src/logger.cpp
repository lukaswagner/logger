#include "../include/logger.hpp"

#include <iostream>

void logger::debug(const std::string& string)
{
    std::cout << string << std::endl;
}
