#include "ContactManager.h"
#include "DNarray.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Function to convert strings to lowercase and compare For sorting
bool convertSTRtoLower(const string &str1, const string &str2)
{
    string lowerStr1 = str1, lowerStr2 = str2;

    transform(lowerStr1.begin(), lowerStr1.end(), lowerStr1.begin(), ::tolower);
    transform(lowerStr2.begin(), lowerStr2.end(), lowerStr2.begin(), ::tolower);

    return lowerStr1 < lowerStr2;
}

// Helper function to clear screen and prompt for new input
void newWindow(const string &message = "")
{
    system("cls");
    cout << message << endl;
    cout << "---------------------------" << endl;
}

// Function to add a new contact
void ContactManager::addContact()
{
    newWindow();

    string Fname, Lname, *phone, *mail, pClass, building, street, city, country;
    int day, month, year, phoneCount, emailCount;
    bool fav;

    // Collect personal details
    newWindow("1- Enter Personal Details:");
    cout << endl;
    cout << "Enter First Name: ";
    cin >> Fname;

    cout << "Enter Last Name: ";
    cin >> Lname;

    cout << "Enter Phone Count: ";
    cin >> phoneCount;
    if (phoneCount > MAX_PHONE_NUMBERS)
    {
        MAX_PHONE_NUMBERS = phoneCount;
    }

    phone = new string[phoneCount];
    for (int i = 0; i < phoneCount; i++)
    {
        cout << "Enter Phone " << i + 1 << ": ";
        cin >> phone[i];
    }

    cout << "Enter Email Count: ";
    cin >> emailCount;
    if (emailCount > MAX_EMAIL_NUMBERS)
    {
        MAX_EMAIL_NUMBERS = emailCount;
    }

    mail = new string[emailCount];
    for (int i = 0; i < emailCount; i++)
    {
        cout << "Enter Email " << i + 1 << ": ";
        cin >> mail[i];
    }
    cout << "Enter Class:";
    cin >> pClass;

    string favInput;
    cout << "Is Favorite (y/n): ";
    cin >> favInput;
    fav = (favInput == "y" || favInput == "Y");

    // Collect Date details
    newWindow("2- Enter Date Details:");
    cout << endl;
    cout << "Enter Date of Birth (DD MM YYYY): ";
    while (!(cin >> day >> month >> year))
    {
        cout << "Invalid date. Please re-enter (DD MM YYYY): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Collect Address details
    newWindow("3- Enter Address Details:");
    cout << endl;
    cout << "Enter Building: ";
    cin >> building;

    cout << "Enter Street: ";
    cin >> street;

    cout << "Enter City: ";
    cin >> city;

    cout << "Enter Country: ";
    cin >> country;


    Person newPerson(Fname, Lname, phone, phoneCount, mail, emailCount, pClass, Date(day, month, year), Address(building, street, city, country), fav);

    if (Contact_List.isFull())
    {
        Contact_List.resize();
    }
    Contact_List.append(newPerson);
    cout << "Contact added successfully!" << endl;

    delete[] phone;
    delete[] mail;
}

// Function to remove a contact
void ContactManager::removeContact()
{
    system("cls");
    cout << "Remove Contact" << endl
         << "---------------\n"
         << endl;

    int ID;
    cout<<"Enter the ID of the contact to remove: ";
    cin >> ID;

    bool found = false;
    for (int i = 0; i < Contact_List.getSize(); i++)
    {
        if (Contact_List.getElement(i).getId() == ID)
        {
            Contact_List.remove(i);
            found = true;
            cout << "Contact removed successfully." << endl;
            break;
        }
    }
    if (!found)
    {
        cout << "Contact with ID " << ID << " not found." << endl;
    }
}

// Function to display all contacts
void ContactManager::displayContacts()
{
    if (Contact_List.isEmpty())
    {
        cout << "No contacts available." << endl;
        return;
    }

    system("cls");
    cout << "Contact List:" << endl;

    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;
    cout << "| " << setw(3) << left << "ID" << " | "
         << setw(11) << left << "First Name" << " | "
         << setw(11) << left << "Last Name" << " | ";

    for (int i = 0; i < MAX_PHONE_NUMBERS; i++)
    {
        string phoneLabel = "Phone " + to_string(i + 1);
        cout << setw(13) << left << phoneLabel << "| ";
    }
    for (int i = 0; i < MAX_EMAIL_NUMBERS; i++)
    {
        string emailLabel = "Email " + to_string(i + 1);
        cout << setw(25) << left << emailLabel << "| ";
    }

    cout << setw(8) << left << "Class" << " | "
         << setw(5) << left << "Fav" << " | "
         << setw(13) << left << "Date of Birth" << " | "
         << setw(30) << left << "Address" << " |"
         << endl;

    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;

    for (int i = 0; i < Contact_List.getSize(); i++)
    {
        Person person = Contact_List.getElement(i);
        Address address = person.getAddress();
        Date date = person.getDate();

        cout << "| " << setw(3) << left << person.getId() << " | "
             << setw(11) << left << person.getFirstName() << " | "
             << setw(11) << left << person.getLastName() << " | ";

        for (int j = 0; j < MAX_PHONE_NUMBERS; j++)
        {
            string phoneNumber;
            if (j < person.getPhoneCount())
            {
                phoneNumber = person.getPhone(j);
            }
            else
            {
                phoneNumber = "-";
            }
            cout << setw(13) << left << phoneNumber << "| ";
        }
        for (int j = 0; j < MAX_EMAIL_NUMBERS; j++)
        {
            string Email;
            if (j < person.getEmailCount())
            {
                Email = person.getEmail(j);
            }
            else
            {
                Email = "-";
            }
            cout << setw(25) << left << Email << "| ";
        }
        cout << setw(8) << left << person.getPersonClass() << " | "
             << setw(5) << left << (person.getIsFavorite() ? "Yes" : "No") << " | "
             << setfill('0') << setw(2) << right << date.getDay() << "/"
             << setw(2) << right << date.getMonth() << "/"
             << setw(4) << left << date.getYear() << setfill(' ') << setw(6) << right << " | "
             << setw(30) << left << address.getBuilding() + ", " + address.getStreet() + ", " + address.getCity() + ", " + address.getCountry() << " | "
             << endl;
    }
    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;
}

void ContactManager::displayFavorites()
{
    system("cls");
    cout << "Favorite Contact List:" << endl;
    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;
    cout << "| " << setw(3) << left << "ID" << " | "
         << setw(11) << left << "First Name" << " | "
         << setw(11) << left << "Last Name" << " | ";

    for (int i = 0; i < MAX_PHONE_NUMBERS; i++)
    {
        string phoneLabel = "Phone " + to_string(i + 1);
        cout << setw(13) << left << phoneLabel << "| ";
    }
    for (int i = 0; i < MAX_EMAIL_NUMBERS; i++)
    {
        string emailLabel = "Email " + to_string(i + 1);
        cout << setw(25) << left << emailLabel << "| ";
    }

    cout << setw(8) << left << "Class" << " | "
         << setw(5) << left << "Fav" << " | "
         << setw(13) << left << "Date of Birth" << " | "
         << setw(30) << left << "Address" << " |"
         << endl;

    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;

    for (int i = 0; i < Contact_List.getSize(); i++)
    {
        if (Contact_List.getElement(i).getIsFavorite() == 1)
        {
            displayPerson(i);
        }
    }
}

void ContactManager::displayPerson(size_t index)
{

    Person person = Contact_List.getElement(index);
    Address address = person.getAddress();
    Date date = person.getDate();

    cout << "| " << setw(3) << left << person.getId() << " | "
         << setw(11) << left << person.getFirstName() << " | "
         << setw(11) << left << person.getLastName() << " | ";

    for (int i = 0; i < MAX_PHONE_NUMBERS; i++)
    {
        string phoneNumber;
        if (i < person.getPhoneCount())
        {
            phoneNumber = person.getPhone(i);
        }
        else
        {
            phoneNumber = "-";
        }
        cout << setw(13) << left << phoneNumber << "| ";
    }
    for (int j = 0; j < MAX_EMAIL_NUMBERS; j++)
    {
        string Email;
        if (j < person.getEmailCount())
        {
            Email = person.getEmail(j);
        }
        else
        {
            Email = "-";
        }
        cout << setw(25) << left << Email << "| ";
    }
    cout << setw(8) << left << person.getPersonClass() << " | "
         << setw(5) << left << (person.getIsFavorite() ? "Yes" : "No") << " | "
         << setfill('0') << setw(2) << right << date.getDay() << "/"
         << setw(2) << right << date.getMonth() << "/"
         << setw(4) << left << date.getYear() << setfill(' ') << setw(6) << right << " | "
         << setw(30) << left << address.getBuilding() + ", " + address.getStreet() + ", " + address.getCity() + ", " + address.getCountry() << " | "
         << endl;

    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;
}

void ContactManager::searchContact()
{
    system("cls");
    cout << "Search Contact: " << endl;
    cout << "-----------------" << endl
         << endl;

    int choice;
    string searchTerm;
    bool isFound = false;

    cout << "Search By: \n 1- ID \n 2- First Name \n 3- Last Name \n 4- Classification \n Enter Your Choice: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter The ID you want to search for: ";
        cin >> searchTerm;

        for (int i = 0; i < Contact_List.getSize(); i++)
        {
            if (Contact_List.getElement(i).getId() == stoi(searchTerm))
            {
                isFound = true;
                system("cls");
                cout << "\n\nContact Found\n"
                     << endl;
                displayPerson(i);
                break;
            }
        }
        if (!isFound)
        {
            cout << "Couldn't find contact with ID: " << searchTerm << endl;
        }
    }

    else if (choice == 2)
    {

        system("cls");
        cout << "Enter The First Name you want to search for: ";
        cin >> searchTerm;
        bool headerPrinted = false; // To control when to print the header

        for (int i = 0; i < Contact_List.getSize(); i++)
        {
            if (Contact_List.getElement(i).getFirstName() == searchTerm)
            {
                isFound = true;
                if (!headerPrinted)
                {
                    system("cls");
                    cout << "Contact Found\n";
                    cout << "-----------------\n"
                         << endl;
                    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;
                    cout << "| " << setw(3) << left << "ID" << " | "
                         << setw(11) << left << "First Name" << " | "
                         << setw(11) << left << "Last Name" << " | ";

                    for (int j = 0; j < MAX_PHONE_NUMBERS; j++)
                    {
                        string phoneLabel = "Phone " + to_string(j + 1);
                        cout << setw(13) << left << phoneLabel << "| ";
                    }
                    for (int i = 0; i < MAX_EMAIL_NUMBERS; i++)
                    {
                        string emailLabel = "Email " + to_string(i + 1);
                        cout << setw(25) << left << emailLabel << "| ";
                    }

                    cout << setw(8) << left << "Class" << " | "
                         << setw(5) << left << "Fav" << " | "
                         << setw(13) << left << "Date of Birth" << " | "
                         << setw(30) << left << "Address" << " |"
                         << endl;

                    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;
                    headerPrinted = true;
                }

                displayPerson(i);
            }
        }
        if (!isFound)
        {
            cout << "Couldn't find contact with First Name: " << searchTerm << endl;
        }
    }
    else if (choice == 3)
    {
        system("cls");
        cout << "Enter The Last Name you want to search for: ";
        cin >> searchTerm;
        bool headerPrinted = false;
        for (int i = 0; i < Contact_List.getSize(); i++)
        {
            if (Contact_List.getElement(i).getLastName() == searchTerm)
            {
                isFound = true;
                if (!headerPrinted)
                {
                    system("cls");
                    cout << "Contact Found\n";
                    cout << "-----------------\n"
                         << endl;
                    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;
                    cout << "| " << setw(3) << left << "ID" << " | "
                         << setw(11) << left << "First Name" << " | "
                         << setw(11) << left << "Last Name" << " | ";

                    for (int j = 0; j < MAX_PHONE_NUMBERS; j++)
                    {
                        string phoneLabel = "Phone " + to_string(j + 1);
                        cout << setw(13) << left << phoneLabel << "| ";
                    }
                    for (int i = 0; i < MAX_EMAIL_NUMBERS; i++)
                    {
                        string emailLabel = "Email " + to_string(i + 1);
                        cout << setw(25) << left << emailLabel << "| ";
                    }

                    cout << setw(8) << left << "Class" << " | "
                         << setw(5) << left << "Fav" << " | "
                         << setw(13) << left << "Date of Birth" << " | "
                         << setw(30) << left << "Address" << " |"
                         << endl;

                    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;
                    headerPrinted = true;
                }

                displayPerson(i);
            }
        }
        if (!isFound)
        {
            cout << "Couldn't find contact with Last Name: " << searchTerm << endl;
        }
    }
    else if (choice == 4)
    {
        system("cls");
        cout << "Enter The Classification you want to search for: ";
        cin >> searchTerm;
        bool headerPrinted = false;
        for (int i = 0; i < Contact_List.getSize(); i++)
        {
            if (Contact_List.getElement(i).getPersonClass() == searchTerm)
            {
                isFound = true;
                if (!headerPrinted)
                {
                    system("cls");
                    cout << "Contact Found\n";
                    cout << "-----------------\n"
                         << endl;
                    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;
                    cout << "| " << setw(3) << left << "ID" << " | "
                         << setw(11) << left << "First Name" << " | "
                         << setw(11) << left << "Last Name" << " | ";

                    for (int j = 0; j < MAX_PHONE_NUMBERS; j++)
                    {
                        string phoneLabel = "Phone " + to_string(j + 1);
                        cout << setw(13) << left << phoneLabel << "| ";
                    }

                    cout << setw(25) << left << "Email" << " | "
                         << setw(8) << left << "Fav" << " | "
                         << setw(5) << left << "Class" << " | "
                         << setw(13) << left << "Date of Birth" << " | "
                         << setw(30) << left << "Address" << " |"
                         << endl;

                    cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;
                    headerPrinted = true;
                }

                displayPerson(i);
            }
        }
        if (!isFound)
        {
            cout << "Couldn't find contact with Last Name: " << searchTerm << endl;
        }
    }
    else
    {
        cout << "Invalid Choice" << endl;
    }
}
void ContactManager::updateContact()
{
    system("cls");
    cout << "Update Contact" << endl;
    cout << "---------------" << endl
         << endl;

    int ID;
    cout << "Enter the ID of the contact to update: ";
    cin >> ID;

    bool found = false;

    for (int i = 0; i < Contact_List.getSize(); i++)
    {
        if (Contact_List.getElement(i).getId() == ID)
        {
            found = true;
            Person newContact = Contact_List.getElement(i);
            int choice;

            cout << " \n 1- First Name \n 2- Last Name  \n 3- Phone Number \n 4- Email \n 5- Class \n 6- Date of Birth \n 7- Address \n 8- Add new Phone Number \n 9- Add new Email \n 0- Cancel " << endl;
            cout << "What Would You Like To Update: ";
            cin >> choice;

            if (choice == 1)
            {
                string newFirstName;
                cout << "Enter New First Name: ";
                cin >> newFirstName;
                newContact.setFirstName(newFirstName);
            }
            else if (choice == 2)
            {
                string newLastName;
                cout << "Enter New Last Name: ";
                cin >> newLastName;
                newContact.setLastName(newLastName);
            }
            else if (choice == 3)
            {
                string *newPhone = new string[MAX_PHONE_NUMBERS];

                system("cls");
                if (newContact.getPhoneCount() > 1)
                {
                    int choice1, choice2;
                    for (int j = 0; j < newContact.getPhoneCount(); j++)
                    {
                        cout << "[" << j + 1 << "] " << newContact.getPhone(j) << endl;
                    }
                    cout << "\nWhich Phone u want to update: ";
                    cin >> choice1;
                    system("cls");
                    cout << "Your Number ->> " << newContact.getPhone(choice1 - 1) << endl;
                    cout << "\n 1- Update \n 2- Delete \n 3- Cancel" << endl;
                    cout << "\nEnter Your Choice: ";
                    cin >> choice2;
                    string newNumber;
                    switch (choice2)
                    {
                    case 1:
                        cout << "Enter new Phone Number: ";
                        cin >> newNumber;
                        for (int i = 0; i < newContact.getPhoneCount(); i++)
                        {
                            if (i == choice1 - 1)
                            {
                                newPhone[i] = newNumber;
                                continue;
                            }
                            newPhone[i] = newContact.getPhone(i);
                        }
                        newContact.setPhone(newContact.getPhoneCount(), newPhone);
                        cout << "\n  ->> Updated Successfully <<-  " << endl;
                        break;
                    case 2:
                        for (int i = 0; i < newContact.getPhoneCount(); i++)
                        {
                            if (i == choice1 - 1)
                            {
                                newPhone[i] = "Deleted";
                                continue;
                            }
                            newPhone[i] = newContact.getPhone(i);
                        }
                        newContact.setPhone(newContact.getPhoneCount(), newPhone);
                        cout << "\n  ->> Deleted Successfully <<-  " << endl;
                        break;
                    case 3:
                        cout << "Cancelled" << endl;
                        break;

                    default:
                        cout << "Invalid Choice! Try Again" << endl;
                        break;
                    }
                }
                else
                {
                    system("cls");
                    cout << "Only one Phone Number Present" << endl;
                    int choice2;
                    cout << "Your Number ->> " << newContact.getPhone(0) << endl;
                    cout << "\n 1- Update \n 2- Delete \n 3- Cancel" << endl;
                    cout << "\nEnter Your Choice: ";
                    cin >> choice2;
                    string newNumber;
                    switch (choice2)
                    {
                    case 1:
                        cout << "Enter new Phone Number: ";
                        cin >> newNumber;
                        newPhone[0] = newNumber;
                        newContact.setPhone(newContact.getPhoneCount(), newPhone);
                        cout << "\n  ->> Updated Successfully <<-  " << endl;
                        break;
                    case 2:
                        newPhone[0] = "Deleted";
                        newContact.setPhone(newContact.getPhoneCount(), newPhone);
                        cout << "\n  ->> Deleted Successfully <<-  " << endl;
                        break;
                    case 3:
                        cout << "Cancelled" << endl;
                        break;

                    default:
                        cout << "Invalid Choice! Try Again" << endl;
                        break;
                    }
                }
            }
            else if (choice == 4)
            {
                string *newEmail = new string[MAX_EMAIL_NUMBERS];

                system("cls");
                if (newContact.getEmailCount() > 1)
                {
                    int choice1, choice2;
                    for (int j = 0; j < newContact.getEmailCount(); j++)
                    {
                        cout << "[" << j + 1 << "] " << newContact.getEmail(j) << endl;
                    }
                    cout << "\nWhich Email u want to update: ";
                    cin >> choice1;
                    system("cls");
                    cout << "Your Email ->> " << newContact.getEmail(choice1 - 1) << endl;
                    cout << "\n 1- Update \n 2- Delete \n 3- Cancel" << endl;
                    cout << "\nEnter Your Choice: ";
                    cin >> choice2;
                    string newMail;
                    switch (choice2)
                    {
                    case 1:
                        cout << "Enter new Email: ";
                        cin >> newMail;
                        for (int i = 0; i < newContact.getEmailCount(); i++)
                        {
                            if (i == choice1 - 1)
                            {
                                newEmail[i] = newMail;
                                continue;
                            }
                            newEmail[i] = newContact.getEmail(i);
                        }
                        newContact.setEmail(newContact.getEmailCount(), newEmail);
                        cout << "\n  ->> Updated Successfully <<-  " << endl;
                        break;
                    case 2:
                        for (int i = 0; i < newContact.getEmailCount(); i++)
                        {
                            if (i == choice1 - 1)
                            {
                                newEmail[i] = "Deleted";
                                continue;
                            }
                            newEmail[i] = newContact.getEmail(i);
                        }
                        newContact.setEmail(newContact.getEmailCount(), newEmail);
                        cout << "\n  ->> Deleted Successfully <<-  " << endl;
                        break;
                    case 3:
                        cout << "Cancelled" << endl;
                        break;

                    default:
                        cout << "Invalid Choice! Try Again" << endl;
                        break;
                    }
                }
                else
                {
                    system("cls");
                    cout << "Only one Email Present" << endl;
                    int choice2;
                    cout << "Your Email ->> " << newContact.getEmail(0) << endl;
                    cout << "\n 1- Update \n 2- Delete \n 3- Cancel" << endl;
                    cout << "\nEnter Your Choice: ";
                    cin >> choice2;
                    string newMail;
                    switch (choice2)
                    {
                    case 1:
                        cout << "Enter new Email: ";
                        cin >> newMail;
                        newEmail[0] = newMail;
                        newContact.setEmail(newContact.getEmailCount(), newEmail);
                        cout << "\n  ->> Updated Successfully <<-  " << endl;
                        break;
                    case 2:
                        newEmail[0] = "Deleted";
                        newContact.setEmail(newContact.getEmailCount(), newEmail);
                        cout << "\n  ->> Deleted Successfully <<-  " << endl;
                        break;
                    case 3:
                        cout << "Cancelled" << endl;
                        break;

                    default:
                        cout << "Invalid Choice! Try Again" << endl;
                        break;
                    }
                }
            }
            else if (choice == 5)
            {
                string newClass;
                cout << "Enter New Class: ";
                cin >> newClass;
                newContact.setPersonClass(newClass);
            }
            else if (choice == 6)
            {
                int day, month, year;
                cout << "Enter New Date of Birth (DD MM YYYY): ";
                cin >> day >> month >> year;
                newContact.setDate(Date(day, month, year));
            }
            else if (choice == 7)
            {
                string building, street, city, country;
                cout << "Enter New Address: " << endl;
                cout << "Building: ";
                cin >> building;
                cout << "Street: ";
                cin >> street;
                cout << "City: ";
                cin >> city;
                cout << "Country: ";
                cin >> country;
                newContact.setAddress(Address(building, street, city, country));
            }
            else if (choice == 8)
            {
                string number;
                int newPhoneCount, totalPhoneCount, lastIndexPhone = 0;
                cout << "How Many number u want to add more: ";
                cin >> newPhoneCount;
                totalPhoneCount = newContact.getPhoneCount() + newPhoneCount;
                string *newPhone = new string[totalPhoneCount];
                for (int j = 0; j < newContact.getPhoneCount(); j++)
                {
                    newPhone[j] = newContact.getPhone(j);
                    lastIndexPhone++;
                }
                for (int i = lastIndexPhone; i < totalPhoneCount; i++)
                {
                    cout << "Enter Phone #" << i + 1 << ": ";
                    cin >> number;
                    newPhone[i] = number;
                }

                newContact.setPhone(totalPhoneCount, newPhone);
                cout << "Added Successfully" << endl;
                delete[] newPhone;
            }
            else if (choice == 9)
            {
                string email;
                int newEmailCount, totalEmailCount, lastIndexEmail = 0;
                cout << "How Many Email u want to add more: ";
                cin >> newEmailCount;
                totalEmailCount = newContact.getEmailCount() + newEmailCount;
                string *newEmail = new string[totalEmailCount];
                for (int j = 0; j < newContact.getEmailCount(); j++)
                {
                    newEmail[j] = newContact.getEmail(j);
                    lastIndexEmail++;
                }
                for (int i = lastIndexEmail; i < totalEmailCount; i++)
                {
                    cout << "Enter Email #" << i + 1 << ": ";
                    cin >> email;
                    newEmail[i] = email;
                }

                newContact.setEmail(totalEmailCount, newEmail);
                cout << "Added Successfully" << endl;
                delete[] newEmail;
            }
            else if (choice == 0)
            {
                cout << "Update Canceled" << endl;
                break;
            }
            else
            {
                cout << "Invalid Choice, Try Again" << endl;
            }

            Contact_List.update(i, newContact);
            break;
        }
    }
    if (!found)
    {
        cout << "Couldn't find contact with ID: " << ID << endl;
    }
}

void ContactManager::sortContacts()
{
    system("cls");
    int choice;
    cout << "Sort By: \n 1- ID \n 2- First Name \n 3- Last Name \n 4- Class \n 0- Cancel \n Enter Your Choice: ";
    cin >> choice;
    if (choice == 1)
    {
        for (int i = 0; i < Contact_List.getSize() - 1; i++)
        {
            for (int j = 0; j < Contact_List.getSize() - i - 1; j++)
            {
                if (Contact_List.getElement(j).getId() > Contact_List.getElement(j + 1).getId())
                {
                    Person temp = Contact_List.getElement(j);
                    Contact_List.getElement(j) = Contact_List.getElement(j + 1);
                    Contact_List.getElement(j + 1) = temp;

                    // swap(Contact_List.getElement(j), Contact_List.getElement(j + 1));

                    // Person temp = Contact_List.getElement(i);
                    // Contact_List.update(i, Contact_List.getElement(i + 1));
                    // cout << "Swapped: " << Contact_List.getElement(j).getFirstName() << " and " << Contact_List.getElement(j + 1).getFirstName() << endl;
                }
            }
        }
        cout << "Sorted By ID Successfully" << endl;
    }
    else if (choice == 2)
    {

        for (int i = 0; i < Contact_List.getSize() - 1; i++)
        {
            for (int j = 0; j < Contact_List.getSize() - i - 1; j++)
            {
                if (convertSTRtoLower(Contact_List.getElement(j + 1).getFirstName(), Contact_List.getElement(j).getFirstName()))
                {
                    Person temp = Contact_List.getElement(j);
                    Contact_List.getElement(j) = Contact_List.getElement(j + 1);
                    Contact_List.getElement(j + 1) = temp;

                    // swap(Contact_List.getElement(j), Contact_List.getElement(j + 1));

                    // Person temp = Contact_List.getElement(i);
                    // Contact_List.update(i, Contact_List.getElement(i + 1));
                    // cout << "Swapped: " << Contact_List.getElement(j).getFirstName() << " and " << Contact_List.getElement(j + 1).getFirstName() << endl;
                }
            }
        }
        cout << "Sorted By First Name Successfully" << endl;
    }
    else if (choice == 3)
    {

        for (int i = 0; i < Contact_List.getSize() - 1; i++)
        {
            for (int j = 0; j < Contact_List.getSize() - i - 1; j++)
            {
                if (convertSTRtoLower(Contact_List.getElement(j + 1).getLastName(), Contact_List.getElement(j).getLastName()))
                {
                    Person temp = Contact_List.getElement(j);
                    Contact_List.getElement(j) = Contact_List.getElement(j + 1);
                    Contact_List.getElement(j + 1) = temp;

                    // swap(Contact_List.getElement(j), Contact_List.getElement(j + 1));

                    // Person temp = Contact_List.getElement(i);
                    // Contact_List.update(i, Contact_List.getElement(i + 1));

                    // cout << "Swapped: " << Contact_List.getElement(j).getFirstName() << " and " << Contact_List.getElement(j + 1).getFirstName() << endl;
                }
            }
        }
        cout << "Sorted By Last Name Successfully" << endl;
    }
    else if (choice == 4)
    {
        for (int i = 0; i < Contact_List.getSize() - 1; i++)
        {
            for (int j = 0; j < Contact_List.getSize() - i - 1; j++)
            {
                if (convertSTRtoLower(Contact_List.getElement(j + 1).getPersonClass(), Contact_List.getElement(j).getPersonClass()))
                {
                    Person temp = Contact_List.getElement(j);
                    Contact_List.getElement(j) = Contact_List.getElement(j + 1);
                    Contact_List.getElement(j + 1) = temp;

                    // swap(Contact_List.getElement(j), Contact_List.getElement(j + 1));

                    // Person temp = Contact_List.getElement(i);
                    // Contact_List.update(i, Contact_List.getElement(i + 1));

                    // cout << "Swapped: " << Contact_List.getElement(j).getFirstName() << " and " << Contact_List.getElement(j + 1).getFirstName() << endl;
                }
            }
        }
        cout << "Sorted By Person Class Successfully" << endl;
    }
    else if (choice == 0)
    {
        cout << "Cancelling..." << endl;
    }
    else
    {
        cout << "Invalid Choice" << endl;
    }
}

void ContactManager::toggleFavorite()
{

    system("cls");
    if (Contact_List.isEmpty())
    {
        cout << "No contacts available." << endl;
    }
    else
    {
        cout << "Contact List:" << endl;
        cout << "------------------" << endl
             << endl;

        cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;
        cout << "| " << setw(3) << left << "ID" << " | "
             << setw(11) << left << "First Name" << " | "
             << setw(11) << left << "Last Name" << " | ";

        for (int i = 0; i < MAX_PHONE_NUMBERS; i++)
        {
            string phoneLabel = "Phone " + to_string(i + 1);
            cout << setw(13) << left << phoneLabel << "| ";
        }
        for (int i = 0; i < MAX_EMAIL_NUMBERS; i++)
        {
            string emailLabel = "Email " + to_string(i + 1);
            cout << setw(25) << left << emailLabel << "| ";
        }

        cout << setw(8) << left << "Class" << " | "
             << setw(5) << left << "Fav" << " | "
             << setw(13) << left << "Date of Birth" << " | "
             << setw(30) << left << "Address" << " |"
             << endl;

        cout << string(106 + MAX_PHONE_NUMBERS * 13 + MAX_EMAIL_NUMBERS * 25, '-') << endl;

        for (int i = 0; i < Contact_List.getSize(); i++)
        {
            displayPerson(i);
        }
    }
    cout << "\n===== Toggle Favorite =====" << endl;
    int ID;
    cout << "Enter The ID that you want to toggle favorite: ";
    cin >> ID;
    bool found = false;
    for (int i = 0; i < Contact_List.getSize(); i++)
    {
        if (Contact_List.getElement(i).getId() == ID)
        {
            found = true;
            Person person = Contact_List.getElement(i);
            if (person.getIsFavorite() == 1)
            {
                person.setIsFavorite(0);
                Contact_List.update(i, person);
                cout << person.getFirstName() << " " << person.getLastName() << ": " << "Is Not Favorite Now." << endl;
                break;
            }
            else
            {
                person.setIsFavorite(1);
                Contact_List.update(i, person);
                cout << person.getFirstName() << " " << person.getLastName() << ": " << "Is Favorite Now." << endl;
                break;
            }
        }
    }

    if (!found)
        cout << "Contact Not Found" << endl;
}
void ContactManager::reverseContacts()
{
    Contact_List.reverse();
    cout << "Reversed Successfully" << endl;
}

void ContactManager::saveContactsToFile()
{
    ofstream file("Contacts.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    for (int i = 0; i < Contact_List.getSize(); i++)
    {
        Person person = Contact_List.getElement(i);
        Address address = person.getAddress();
        Date date = person.getDate();

        file << person.getId() << ","
             << person.getFirstName() << ","
             << person.getLastName() << ","
             << person.getPhoneCount() << ","; 

        for (int j = 0; j < person.getPhoneCount(); j++)
        {
            file << person.getPhone(j);
            if (j < person.getPhoneCount() - 1) 
            {
                file << ","; 
            }
        }

        file << "," << person.getEmailCount() << ",";
        for (int j = 0; j < person.getEmailCount(); j++)
        {
            file << person.getEmail(j);
            if (j < person.getEmailCount() - 1) 
            {
                file << ","; 
            }
        }

        file << "," << person.getPersonClass() << ","
             << (person.getIsFavorite() ? 'y' : 'n') << ","
             << date.getDay() << ","
             << date.getMonth() << ","
             << date.getYear() << ","
             << address.getBuilding() << ","
             << address.getStreet() << ","
             << address.getCity() << ","
             << address.getCountry() << endl;
    }

    file.close();
    cout << "All contacts saved successfully!" << endl;
}

void ContactManager::loadContactsFromFile()
{
    ifstream file("Contacts.txt");
    if (!file.is_open())
    {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    string line;
    int loadedContactsCount = 0; 
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string Fname, Lname, pClass, building, street, city, country;
        int id, day, month, year, phoneCount, emailCount;
        bool fav;

        try
        {
            getline(ss, line, ',');
            id = stoi(line);

            getline(ss, Fname, ',');
            getline(ss, Lname, ',');

            getline(ss, line, ',');
            phoneCount = stoi(line);

            string *phone = new string[phoneCount];
            for (int i = 0; i < phoneCount; ++i)
            {
                getline(ss, phone[i], ',');
            }

            getline(ss, line, ',');
            emailCount = stoi(line);

            string *mail = new string[emailCount];
            for (int i = 0; i < emailCount; ++i)
            {
                getline(ss, mail[i], ',');
            }

            getline(ss, pClass, ',');

            getline(ss, line, ',');
            fav = (line == "y");

            getline(ss, line, ',');
            day = stoi(line);
            getline(ss, line, ',');
            month = stoi(line);
            getline(ss, line, ',');
            year = stoi(line);

            getline(ss, building, ',');
            getline(ss, street, ',');
            getline(ss, city, ',');
            getline(ss, country, ',');

            Person newPerson(Fname, Lname, phone, phoneCount, mail, emailCount, pClass, Date(day, month, year), Address(building, street, city, country), fav);
            newPerson.setId(id);

            if (Contact_List.isFull())
            {
                Contact_List.resize();
            }
            Contact_List.append(newPerson);
            loadedContactsCount++; 
            delete[] phone;
            delete[] mail;
        }
        catch (const invalid_argument &e)
        {
            cout << "Invalid input in line: " << line << " - " << e.what() << endl;
        }
        catch (const out_of_range &e)
        {
            cout << "Input out of range in line: " << line << " - " << e.what() << endl;
        }
    }
    file.close();
    cout << "Contacts loaded successfully! Total loaded: " << loadedContactsCount << endl;
}
