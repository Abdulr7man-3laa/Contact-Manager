#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
using namespace std;

class Address
{
private:
    string building;
    string street;
    string city;
    string country;

public:
    // Default constructor to initialize address to default values
    Address();
    // Constructor to initialize address with specific values
    Address(string newBuilding, string newStreet, string newCity, string newCountry);

    // Functions to set Address values
    void setBuilding(string newBuilding);
    void setStreet(string newStreet);
    void setCity(string newCity);
    void setCountry(string newCountry);

    // Functions to get Address values
    string getBuilding() const;
    string getStreet() const;
    string getCity() const;
    string getCountry() const;
};

#endif