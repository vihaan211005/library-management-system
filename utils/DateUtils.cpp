#include <ctime>
#include <string>
int calculateDateDifference(time_t time1, time_t time2) {
    return (time2 - time1) / (60 * 60 * 24);
}

time_t getCurrentTime() {
    return time(nullptr);
}

std::string timeToString(time_t timeValue) {
    char       buffer[100];
    struct tm *timeInfo = localtime(&timeValue);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return std::string(buffer);
}
