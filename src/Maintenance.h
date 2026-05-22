/*
This is the header file for the maintenance utilities it will hold definitions for the functions
this is a helper file
Formatting
*/

#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <string>
#include <ctime> // for time_t Return/Checkout dates etc.

// Converting to readable date
std::string formatDate(std::time_t rawTime);

//getting current date
std::time_t getToday();

//Coverting date string to time_t
std::time_t parseDate(const std::string& dateStr);

#endif // MAINTENANCE_H
