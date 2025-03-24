#include "Date.h"

// Default constructor to initialize date to default values
Date::Date()
{
    day = 1;
    month = 1;
    year = 2000;
}

// Constructor to initialize date with specific values
Date::Date(int newDay, int newMonth, int newYear)
{
    day = newDay;     // Set the day to the provided value
    month = newMonth; // Set the month to the provided value
    year = newYear;   // Set the year to the provided value
}

// Functions to set date values
void Date::setDay(int newDay)
{
    day = newDay; // Update the day to the new value
}
void Date::setMonth(int newMonth)
{
    month = newMonth; // Update the month to the new value
}
void Date::setYear(int newYear)
{
    year = newYear; // Update the year to the new value
}

// Functions to get date values
int Date::getDay() const
{
    return day;
}
int Date::getMonth() const
{
    return month;
}
int Date::getYear() const
{
    return year;
}