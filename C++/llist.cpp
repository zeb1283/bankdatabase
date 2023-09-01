/*****************************************************************
//  NAME:        Zeb Lakey
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 25, 2023
//
//  FILE:        llist.c
//
//  DESCRIPTION:
//  Defines all database functions that will be utilized when
//  accessing the database.
//
//
****************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "llist.h"
#include "record.h"
using namespace std;

/*****************************************************************
//  Function name: addrecord
//
//  DESCRIPTION:   Adds a record to the database
//                
//
//  Parameters:    int accountno : The account number
//                 char name [] : The name of the user
//                 char address [] :The address of the user
//                               
//  Return values: none
//                 
//
****************************************************************/

void llist::addRecord(int uaccountno, char uname[], char uaddress[])
{
    record* temp;
    record* temp2;
    record* urecord;
    urecord = new record;
    #ifdef DEBUG
    cout << "\n\n\n*** DEBUG function: addRecord" << endl;
    cout << " param:\n int accountno " << uaccountno << endl;
    cout << "\n char name[] " << uname << endl;
    cout << "char address " << uaddress << "\n\n\n";
    #endif
    urecord->accountno = uaccountno;
    strcpy(urecord->name, uname);
    strcpy(urecord->address, uaddress);
    urecord->next = NULL;
    temp = start;
    temp2 = NULL;

    if (start == NULL || uaccountno < temp->accountno)
    {
        urecord->next = start;
        start = urecord;
    }
    else
    {
        while (temp != NULL && temp->accountno <= uaccountno)
        {
            temp2 = temp;
            temp = temp->next;
        }
        temp2->next = urecord;
        urecord->next = temp;
    }
}

/*****************************************************************
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints every record in the database
//
//  Parameters:    NONE
//
//  Return values: none
//
****************************************************************/

void llist::printAllRecords()
{
    record *temp;
    temp = start;
    while (temp != NULL)
    {
        cout << "Account Number: " << temp->accountno << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Address: " << temp->address << "\n\n";
        temp = temp->next;
    }
}

/*****************************************************************
//  Function name: findRecord
//
//  DESCRIPTION:   finds a record using the account number as key
// 
//  Parameters:    int accountno: the account number to be found              
//                         
// 
//  Return values:  positive number: # of found record under accountno
//                  -1: No record under accountno
//                
***************************************************************/

int llist::findRecord(int accountno)
{
    record *temp;
    int found;
    found = 0;
    temp = start;
    #ifdef DEBUG
    cout << "\n\n\n*** DEBUG function: findRecord \n param:" << endl;
    cout << "int accountno" << accountno << "\n\n\n";
    #endif
    while (temp != NULL)
    {
        if (temp->accountno == accountno)
        {
            cout << "Account Number: " << temp->accountno << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Address: " << temp->address << "\n\n\n";
            found++;
        }
        temp = temp->next;
    }
    if (found == 0)
    {
        found--;
    }
    return found;
}

/*****************************************************************
//  Function name: deleteRecord
//
//  DESCRIPTION:   Gets the address
// 
//  Parameters:    accountno (int): The account number to be deleted         
// 
//  Return values:  -1: No record under accountno
//                  deleted: Number of records deleted
//
***************************************************************/

int llist::deleteRecord(int uaccountno)
{
    int deleted;
    record* temp;
    record* temp2;
    deleted = 0;
    temp = start;
    temp2 = NULL;
    #ifdef DEBUG
    cout << "\n\n\n*** DEBUG function: deleteRecord \n param:" << endl;
    cout << "int accountno " << uaccountno << "\n\n\n";
    #endif
    while (temp != NULL)
    {
        if (temp->accountno == uaccountno)
        {
            if (temp2 == NULL)
            {
                start = temp->next;
                delete temp;
                temp = start;
                deleted++;
            }
            else
            {
                temp2->next = temp->next;
                delete temp;
                temp = temp2->next;
                deleted++;
            }
        }
        else
        {
            temp2 = temp;
            temp = temp->next;
        }
    }
    if (deleted == 0)
    {
        deleted--;
    }
    return deleted;
}

/*****************************************************************
//  Function name: writefile
//
//  DESCRIPTION:   Writes information to file
//                 
//  Parameters:    NONE
// 
//  Return values:  0: No record under accountno
//                  invalid: number of nodes converted to file
//
***************************************************************/

int llist::writefile()
{
    record *temp;
    int invalid;
    ofstream file;
    file.open(filename);
    temp = start;
    invalid = 0;
    if (file == NULL)
    {
        invalid = -1;
    }
    else
    {
        while (temp != NULL)
        {
            file << temp->accountno << endl;
            file << temp->name << endl;
            file << temp->address << endl;
            temp = temp->next;
            invalid++;
        }
    }
    file.close();
    return invalid;
}

/*****************************************************************
//  Function name: readfile
//
//  DESCRIPTION:   reads from file to the linked list
//                 
//  Parameters:    NONE         
// 
//  Return values:  -1: No record under accountno
//                  positive number: number of records added to linked list
//
***************************************************************/

int llist::readfile()
{
    int accountno;
    char name[30];
    char address[50];
    int invalid;
    ifstream file;
    file.open(filename);
    invalid = 0;
    if (file == NULL)
    {
        invalid = -1;
    }
    else
    {
        while (file >> accountno >> name >> address)
        {
            addRecord(accountno, name, address);
        }
    }
    file.close();
    return invalid;
}

/*****************************************************************
//  Function name: cleanup
//
//  DESCRIPTION:   Called at the end of the function to clear up heap space
// 
//  Parameters:    NONE 
// 
//  Return values:  0: No record under accountno
//                  uaccountno: account number that was deleted
//
***************************************************************/

void llist::cleanup()
{
    record *temp;
    record *temp2;
    temp = start;
    temp2 = NULL;
    while (temp != NULL)
    {
        temp2 = temp->next;
        delete temp;
        temp = temp2;
    }
    start = NULL;
}

/*****************************************************************
//  Function name: llist (constructor)
//
//  DESCRIPTION:   standard no args constructor for list object
// 
//  Parameters:    NONE 
// 
//  Return values:  NONE
//
***************************************************************/

llist::llist()
{
    start = NULL;
    strcpy(filename, "save.txt");
    readfile();
}

/*****************************************************************
//  Function name: llist (constructor)
//
//  DESCRIPTION:   standard no args constructor for list object
// 
//  Parameters:    list (char[]): string for someone to hardcode in
//                 a non-default file name
// 
//  Return values:  NONE
//
***************************************************************/

llist::llist(char list[])
{
    start = NULL;
    strcpy(filename, list);
    readfile();
}

/*****************************************************************
//  Function name: llist (destructor)
//
//  DESCRIPTION:   standard no args destructor for list object
// 
//  Parameters:    NONE 
// 
//  Return values:  NONE
//
***************************************************************/

llist::~llist()
{
    writefile();
    cleanup();
}
