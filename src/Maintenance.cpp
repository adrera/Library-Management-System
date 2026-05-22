/*
This is the implementation file for the maintenance functions
this is a helper file
Formatting
*/

#include "Maintenance.h"
#include <sstream>
#include <iomanip>

// Converting to readable date
std::string formatDate(std::time_t rawTime) {
    if (rawTime <= 0)
        return "N/A";

    std::tm* timeInfo = std::localtime(&rawTime);

    std::ostringstream out;
    out << std::setfill('0')
        << std::setw(2) << timeInfo->tm_mon + 1 << "/"
        << std::setw(2) << timeInfo->tm_mday << "/"
        << (timeInfo->tm_year + 1900);

    return out.str();
}

//getting current date
std::time_t getToday() {
    std::time_t now = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&now);

    timeInfo->tm_hour = 0;
    timeInfo->tm_min  = 0;
    timeInfo->tm_sec  = 0;

    return std::mktime(timeInfo);
}

//Coverting date string to time_t
std::time_t parseDate(const std::string& dateStr) {
    int month, day, year;
    char slash1, slash2;

    std::istringstream in(dateStr);
    if (!(in >> month >> slash1 >> day >> slash2 >> year))
        return -1;

    if (slash1 != '/' || slash2 != '/')
        return -1;

    std::tm timeInfo = {};
    timeInfo.tm_mon  = month - 1;
    timeInfo.tm_mday = day;
    timeInfo.tm_year = year - 1900;

    return std::mktime(&timeInfo);
}

//Maintenance.cpp