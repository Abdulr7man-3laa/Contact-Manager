#ifndef DATA_H
#define DATA_H



class Date
{
private:
    int day, month, year;

public:
    Date();                                      // Default constructor to initialize date to default values
    Date(int newDay, int newMonth, int newYear); // Constructor to initialize date with specific values

    // Functions to set date values
    void setDay(int newDay);
    void setMonth(int newMonth);
    void setYear(int newYear);

    // Functions to get date values
    int getDay() const;
    int getMonth() const;
    int getYear() const;
};

#endif