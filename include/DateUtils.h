#pragma once

#include <ctime>
#include <string>

int         calculateDateDifference(time_t time1, time_t time2);
time_t      getCurrentTime();
std::string timeToString(time_t timeValue);