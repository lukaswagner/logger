#include "globals.hpp"

bool logger::g_enabled = false;
int logger::g_contextLength = 10;
bool logger::g_printTime = true;
std::string logger::g_timeFormat = "%H:%M:%S";
std::shared_ptr<logger::Output> logger::g_output = nullptr;
