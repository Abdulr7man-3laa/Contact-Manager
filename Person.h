#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

#include "Address.h" // Include the Address class
#include "Date.h"    // Include the Date class

using namespace std;

static int nextID = 1;            // Static variable to keep track of the next available ID
static int MAX_PHONE_NUMBERS = 0; // Static variable to keep track of the maximum number of phone numbers
static int MAX_EMAIL_NUMBERS = 0; // Static variable to keep track of the maximum number of email addresses

class Person
{
private:
    int id, phoneCount, emailCount;
    string firstName;
    string lastName;
    string *phone;
    string *email;
    string personClass;
    Date date;
    Address address;
    bool isFavorite; // Flag to indicate if the person is a favorite

public:
    // Default constructor to initialize person with default values
    Person();
    // Constructor to initialize person with specific values
    Person(string newFirstName, string newLastName, string *newPhone, int newPhoneCount, string *newEmail, int newEmailCount, string newPersonClass, Date newDate, Address newAddress, bool newIsFavorite);

    // Functions to get Person's Details
    int getId();
    string getFirstName() const;
    string getLastName() const;
    string getPhone(int index) const;
    string getEmail(int index) const;
    bool getIsFavorite() const;
    string getPersonClass() const;
    Date getDate() const;
    Address getAddress() const;
    int getPhoneCount() const;
    int getEmailCount() const;

    // Functions to set Person's Details
    void setId(int newId);
    void setFirstName(string newFirstName);
    void setLastName(string newLastName);
    void setPhone(int newPhoneCount, string *newPhone);
    void setEmail(int newEmailCount, string *newEmail);
    void setIsFavorite(bool newIsFavorite);
    void setPersonClass(string newPersonClass);
    void setDate(Date newDate);
    void setAddress(Address newAddress);
};

#endif