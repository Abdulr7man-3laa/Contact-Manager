#include "ContactManager.h"
#include "Person.h"
#include "Address.h"
#include "DNarray.h"
#include "Date.h"
#include <iostream>
#include <iomanip>

void waitForEnter()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

string centerText(const string &text, int width)
{
    int padding = width - text.length();
    int leftPadding = padding / 2;
    int rightPadding = padding - leftPadding;

    return string(leftPadding, ' ') + text + string(rightPadding, ' ');
}

void displayMainMenu()
{
    system("cls");
    int width = 50; // Total width of the menu
    cout << "--------------------------------------------------" << endl;
    cout << "|" << centerText("Contact Manager Menu", width - 2) << "|" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "|" << centerText("1. Add Contact", width - 2) << "|" << endl;
    cout << "|" << centerText("2. Sort Contacts", width - 2) << "|" << endl;
    cout << "|" << centerText("3. Remove Contact", width - 2) << "|" << endl;
    cout << "|" << centerText("4. Search Contact", width - 2) << "|" << endl;
    cout << "|" << centerText("5. Update Contact", width - 2) << "|" << endl;
    cout << "|" << centerText("6. Toggle Favorite", width - 2) << "|" << endl;
    cout << "|" << centerText("7. Reverse Contact List", width - 2) << "|" << endl;
    cout << "|" << centerText("8. Display All Contacts", width - 2) << "|" << endl;
    cout << "|" << centerText("9. Save Contacts to File", width - 2) << "|" << endl;
    cout << "|" << centerText("10. Load Contacts from File", width - 2) << "|" << endl;
    cout << "|" << centerText("11. Display Favorite Contacts", width - 2) << "|" << endl;
    cout << "|" << centerText("0. Exit", width - 2) << "|" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    ContactManager manager;
    int choice;

    do
    {
        displayMainMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            manager.addContact();
            waitForEnter();
            break;
        case 2:
            manager.sortContacts();
            waitForEnter();
            break;
        case 3:
            manager.removeContact();
            waitForEnter();
            break;
        case 4:
            manager.searchContact();
            waitForEnter();
            break;
        case 5:
            manager.updateContact();
            waitForEnter();
            break;
        case 6:
            manager.toggleFavorite();
            waitForEnter();
            break;
        case 7:
            manager.reverseContacts();
            waitForEnter();
            break;
        case 8:
            manager.displayContacts();
            waitForEnter();
            break;
        case 9:
            manager.saveContactsToFile();
            waitForEnter();
            break;
        case 10:
            manager.loadContactsFromFile();
            waitForEnter();
            break;
        case 11:
            manager.displayFavorites();
            waitForEnter();
            break;
        case 0:
            cout << "Thank you for using Contact Manager. Goodbye!" << endl;
            waitForEnter();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            waitForEnter();
            break;
        }
    } while (choice != 0);

    return 0;
}