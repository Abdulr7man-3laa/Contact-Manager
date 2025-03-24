#include "Address.h"

Address::Address()
{
    building = "";
    street = "";
    city = "";
    country = "";
}
Address::Address(string newBuilding, string newStreet, string newCity, string newCountry)
{
    building = newBuilding; // Set the building to the provided value
    street = newStreet;     // Set the street to the provided value
    city = newCity;         // Set the city to the provided value
    country = newCountry;   // Set the country to the provided value
}

// Functions to set Address values
void Address::setBuilding(string newBuilding)
{
    building = newBuilding; // Update the building to the new value
}
void Address::setStreet(string newStreet)
{
    street = newStreet; // Update the street to the new value
}
void Address::setCity(string newCity)
{
    city = newCity; // Update the city to the new value
}
void Address::setCountry(string newCountry)
{
    country = newCountry; // Update the country to the new value
}

// Functions to get Address values
string Address::getBuilding() const
{
    return building;
}
string Address::getStreet() const
{
    return street;
}

string Address::getCity() const
{
    return city;
}

string Address::getCountry() const
{
    return country;
}