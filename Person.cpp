#include "Person.h"

// Default constructor to initialize person with default values
Person::Person()
{
    id = 0;
    phone = nullptr;
    email = nullptr;
    phoneCount = 0;
    emailCount = 0;
}
Person::Person(string newFirstName, string newLastName, string *newPhone, int newPhoneCount, string *newEmail, int newEmailCount, string newPersonClass, Date newDate, Address newAddress, bool newIsFavorite)
{
    id = nextID++; // Assign a unique ID and increment nextID
    firstName = newFirstName;
    lastName = newLastName;
    isFavorite = newIsFavorite;
    personClass = newPersonClass;
    date = newDate;
    address = newAddress;
    phoneCount = newPhoneCount;
    phone = new string[phoneCount];
    for (int i = 0; i < phoneCount; i++)
    {
        phone[i] = newPhone[i];
    }
    emailCount = newEmailCount;
    email = new string[emailCount];
    for (int i = 0; i < emailCount; i++)
    {
        email[i] = newEmail[i];
    }
    if (phoneCount > MAX_PHONE_NUMBERS)
    {
        MAX_PHONE_NUMBERS = phoneCount;
    }
    if (emailCount > MAX_EMAIL_NUMBERS)
    {
        MAX_EMAIL_NUMBERS = emailCount;
    }
    
}

// Functions to get Person's Details
int Person::getId()
{
    return id;
}
int Person::getPhoneCount() const
{
    return phoneCount;
}
int Person::getEmailCount() const
{
    return emailCount;
}
string Person::getFirstName() const
{
    return firstName;
}

string Person::getLastName() const
{
    return lastName;
}

string Person::getEmail(int index) const
{
    if (index >= emailCount || index < 0)
    {
        throw out_of_range("Index out of range");
    }
    return email[index] != "" ? email[index] : "-";
}

bool Person::getIsFavorite() const
{
    return isFavorite;
}

string Person::getPersonClass() const
{
    return personClass;
}

Date Person::getDate() const
{
    return date;
}

Address Person::getAddress() const
{
    return address;
}

// Functions to set Person's Details
void Person::setId(int newId)
{
    id = newId; // Update the ID to the new value
}
void Person::setFirstName(string newFirstName)
{
    firstName = newFirstName; // Update the first name to the new value
}
void Person::setLastName(string newLastName)
{
    lastName = newLastName; // Update the last name to the new value
}

string Person::getPhone(int index) const
{
    if (index >= phoneCount || index < 0)
    {
        throw out_of_range("Index out of range");
    }
    return phone[index] != "" ? phone[index] : "-";
}
void Person::setPhone(int newPhoneCount, string *newPhone)
{
    delete[] phone;
    phoneCount = newPhoneCount;
    phone = new string[phoneCount];
    for (int i = 0; i < phoneCount; i++)
    {
        phone[i] = newPhone[i];
    }
    MAX_PHONE_NUMBERS = phoneCount;
}

void Person::setEmail(int newEmailCount, string *newEmail)
{
    delete[] email;
    emailCount = newEmailCount;
    email = new string[emailCount];
    for (int i = 0; i < emailCount; i++)
    {
        email[i] = newEmail[i];
    }
    MAX_EMAIL_NUMBERS = emailCount;
}
void Person::setIsFavorite(bool newIsFavorite)
{
    isFavorite = newIsFavorite; // Update the isFavorite to the new value
}
void Person::setPersonClass(string newPersonClass)
{
    personClass = newPersonClass; // Update the personClass to the new value
}
void Person::setDate(Date newDate)
{
    date = newDate; // Update the date to the new value
}
void Person::setAddress(Address newAddress)
{
    address = newAddress; // Update the address to the new value
}
