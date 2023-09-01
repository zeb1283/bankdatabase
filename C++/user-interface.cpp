/*****************************************************************
//  NAME:        Zeb Lakey
//
//  HOMEWORK:    Project 2
// 
//   CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 25, 2023
//
//  FILE:        user-interface.cpp
//
//   DESCRIPTION:
//   Contains main method that takes the general user input and
//   stores values in different variables, and getaddress that
//   obtains the user address
//
***************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "llist.h"
#include "record.h"
void getaddress(char[], int);
using namespace std;

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   takes user input so that the user can use multiple
//                 different commands
//                 
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : program done
//                 
//
****************************************************************/

int main(int argc, char*argv[])
{
    char command[20];
    int i;
    llist *list = new llist();
    char name[20];
    int accountno;
    char address[50];
    int terminate;
    int numargs;
    terminate = 0;
    accountno = 0;
    #ifdef DEBUG
    cout << "\n****** Now entering debug mode for project2.\n\n";
    #endif
    if (terminate == 0)
    {
        i = 0;
        cout << "Hello! This is a program that mimics a bank database\n\n";
        cout << "Please choose a menu option:\nadd: Add a new record in the database" << endl;
        cout << "printall: Print all records in database" << endl;
        cout << " find: Find record(s) within a specific account #" << endl;
        cout << "delete: Delete record(s) from the database using account # as a key" << endl;
        cout << " quit: quit the program\n" << endl;
        while (i == 0)
        {
            accountno = 0;
            cout << "Please enter a command: ";
            cin.get(command, 20);
            if (strncmp("add", command, strlen(command)) == 0)
            {
                cout << "You have selected add.\n";
                cout << "Please enter an account number: ";
                while (!(cin >> accountno) || accountno <= 0)
                {
                    cout << "Please enter a positive integer.(Error B)";
                    cin.clear();
                    cin.ignore(20, '\n');
                }
                cout << "Please enter your name: ";
                cin.ignore();
                cin.getline(name, 20);
                getaddress(address, 0);
                cout << "Record has been added.\n";
                list->addRecord(accountno, name, address);
                accountno = 0;
            }
            else if (strncmp("printall", command, strlen(command)) == 0)
            {
                list->printAllRecords();
                cin.clear();
                cin.ignore(20, '\n');
                cout << "\n Records printed. If nothing printed here, no records exist." << endl;
            }
            else if (strncmp("find", command, strlen(command)) == 0)
            {
                accountno = 0;
                cout << "Enter an account number you would like to find the record for: " << endl;
                while ( !(cin >> accountno) || accountno <= 0)
                {
                    cout << "Please enter a positive integer.";
                    cin.clear();
                    cin.ignore(20, '\n');
                }
                cin.clear();
                cin.ignore(20, '\n');
                numargs = list->findRecord(accountno);
                if (numargs >= 0)
                {
                    cout << "\n" << numargs << " record(s) found!" << endl;
                }
                else
                {
                    cout << "\nNo record found under this account number." << endl;
                }
            }
            else if (strncmp("delete", command, strlen(command)) == 0)
            {
                accountno = 0;
                cout << "Please enter an account number to delete: " << endl;
                while ( !(cin >> accountno) || accountno <= 0)
                {
                    cout << "Please enter a positive integer.(Error B)" << endl;
                    cin.clear();
                    cin.ignore(20, '\n');
                }
                cin.clear();
                cin.ignore(20, '\n');
                cout << "Account number input complete." << endl;
                numargs = list->deleteRecord(accountno);
                if (numargs >= 0)
                {
                    cout << "\n" << numargs << " record(s) deleted!" << endl;
                }
                else
                {
                    cout << "\nNo record found under this account number." << endl;
                }
            }
            else if (strncmp("quit", command, strlen(command)-1) == 0)
            {
                cout << "\nquitting" << endl;
                i = 1;
                delete list;
            }
            else
            {
                cout << "Erroneous input, please press enter to try again" << endl;
                cin.clear();
                cin.ignore(20, '\n');
            }
        }
    }
    return 0;
}

/*****************************************************************
//  Function name: getaddress
//
//  DESCRIPTION:   Gets the address
//                 
// 
//  Parameters:    address (char[]) the address that the user input
//                                  is entered into
//                 length (int)     the length of the address         
// 
//  Return values:  none
//                
//
***************************************************************/

void getaddress(char address[], int length)
{
    int i;
    int character;
    int loop;
    i = 0;
    character = 0;
    loop = 0;
    #ifdef DEBUG
    cout << "\n\n\n*** debugmode FUNCTION: getaddress\n address[] " << address << endl;
    cout << "length " << length << "\n\n\n";
    #endif
    cout << "Please enter your address" << endl;
    cout << "Press enter twice when done entering address." << endl;
    while (loop == 0 && (character = cin.get()) != -1)
    {
        if (character == '\n')
        {
            if (i > 0 && address[i-1] == '\n')
            {
                loop = 1;
                address[i-1] = '\0';
            }
        }
        address[i++] = character;
        length++;
        if (length == 49)
        {
            loop = 1;
            while (cin.get() != '\n');
            cout << "Address input too long, added up to the 49th character" << endl;
            address[i-1] = '\0';
        }
    }
    cout << "Address input complete." << endl;
}
