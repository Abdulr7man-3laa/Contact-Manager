#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include "Person.h"
#include "DNarray.h"
class ContactManager
{
private:
    DNarray<Person> Contact_List; // Dynamic array to store a list of Person objects representing the Contact List

public:
    void addContact();                // Function to Add a new contact to the list
    void removeContact();             // Function to Remove a contact from the list
    void updateContact();             // Function to Update the information of an existing contact
    void displayContacts();           // Function to Display all contacts in the list
    void displayFavorites();          // Function to Display only favorite contacts
    void sortContacts();              // Function to Sort the contact list
    void searchContact();             // Function to Search for a contact
    void displayPerson(size_t index); // Function to Display details of a specific contact at the given index
    void toggleFavorite();            // Function to Toggle the "favorite" status of a contact (add or remove from favorites)
    void reverseContacts();           // Function to Reverse the order of the contact list
    void saveContactsToFile();        // Function to Save all contacts to a file (for backup purposes)
    void loadContactsFromFile();      // Function to load contacts from a file (for recovery purposes)
};

#endif