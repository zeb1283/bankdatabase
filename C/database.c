/*****************************************************************
//  NAME:        Zeb Lakey
//
//  HOMEWORK:    3b
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        February 8, 2023
//
//  FILE:        database.c
//
//  DESCRIPTION:
//  Defines all database functions that will be utilized when
//  accessing the database.
//
//
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
extern int debugmode;

/*****************************************************************
//  Function name: addrecord
//
//  DESCRIPTION:   Adds a record to the database
//                
//
//  Parameters:    struct record** start :The address of first record
//                 int accountno : The account number
//                 char name [] : The name of the user
//                 char address [] :The address of the user
//                               
//
//  Return values: none
//                 
//
****************************************************************/

void addRecord(struct record** start, int uaccountno, char uname[], char uaddress[])
{
    struct record* temp;
    struct record* temp2;
    struct record* urecord;
    urecord = (struct record*) malloc(sizeof(struct record));
    if (debugmode == 1)
    {
        printf("\n\n\n***** DEBUGMODE function: addRecord \n param: \n struct record** start \n int accountno %d\nchar name[] %s\nchar address %s\n\n\n", uaccountno, uname, uaddress);
    }
    urecord->accountno = uaccountno;
    strcpy(urecord->name, uname);
    strcpy(urecord->address, uaddress);
    urecord->next = NULL;
    temp = *start;
    temp2 = NULL;

    if (*start == NULL || uaccountno < temp->accountno)
    {
        urecord->next = *start;
        *start = urecord;
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
//  Parameters:    struct record* start :The first record
//
//  Return values: none
//
****************************************************************/

void printAllRecords(struct record * start)
{
    struct record *temp;
    temp = start;
    if (debugmode == 1)
    {
        printf("\n\n\n***** DEBUGMODE function: printAllRecords \n param: \n struct record* start \n\n\n");
    }
    while (temp != NULL)
    {
        printf("Account Number: %d\nName: %s\nAddress: %s\n\n", temp->accountno, temp->name, temp->address);
        temp = temp->next;
    }
}

/*****************************************************************
//  Function name: findRecord
//
//  DESCRIPTION:   finds a record using the account number as key
// 
//  Parameters:    record* start: the first record
//                 int accountno: the account number to be found              
//                         
// 
//  Return values:  positive number: # of found record under accountno
//                  -1: No record under accountno
//                
***************************************************************/

int findRecord(struct record * start, int accountno)
{
    struct record *temp;
    int found;
    found = 0;
    temp = start;
    if (debugmode == 1)
    {
        printf("\n\n\n***** DEBUGMODE function: findRecord \n param: \n struct record* start \n int accountno %d\n\n\n", accountno);
    }
    while (temp != NULL)
    {
        if (temp->accountno == accountno)
        {
            printf("Account Number: %d\nName: %s\nAddress: %s\n\n", temp->accountno, temp->name, temp->address);
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
//  Parameters:    struct record** start: the address of the first record
//                 accountno (int): The account number to be deleted         
// 
//  Return values:  -1: No record under accountno
//                  deleted: Number of records deleted
//
***************************************************************/

int deleteRecord(struct record ** start, int uaccountno)
{
    int deleted;
    struct record* temp;
    struct record* temp2;
    deleted = 0;
    temp = *start;
    temp2 = NULL;
    if (debugmode == 1)
    {
        printf("\n\n\n***** DEBUGMODE function: deleteRecord \n param: \n struct record** start \n int accountno %d\n\n\n", uaccountno);
    }
    while (temp != NULL)
    {
        if (temp->accountno == uaccountno)
        {
            if (temp2 == NULL)
            {
                *start = temp->next;
                free(temp);
                temp = *start;
                deleted++;
            }
            else
            {
                temp2->next = temp->next;
                free(temp);
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
// 
//  Parameters:    struct record* start: the first record
// 
//  Return values:  0: No record under accountno
//                  invalid: number of nodes converted to file
//
***************************************************************/

int writefile(struct record *start, char filename[])
{
    FILE *file;
    struct record *temp;
    int invalid;
    if (debugmode == 1)
    {
        printf("\n\n\n***** DEBUGMODE function: writefile \n param: \n struct record* start\nchar filename[]: %s \n\n\n", filename);
    }
    file = fopen(filename, "w");
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
            fprintf(file, "%d,%s,%s\n", temp->accountno, temp->name, temp->address);
            temp = temp->next;
            invalid++;
        }
    }
    fclose(file);
    return invalid;
}

/*****************************************************************
//  Function name: readfile
//
//  DESCRIPTION:   reads from file to the linked list
//                 
// 
//  Parameters:    struct record** start: the address of the first record
//                 filename (char[]): The file name         
// 
//  Return values:  -1: No record under accountno
//                  positive number: number of records added to linked list
//
***************************************************************/

int readfile(struct record **start, char filename[])
{
    FILE *file;
    int accountno;
    char name[30];
    char address[50];
    int invalid;
    if (debugmode == 1)
    {
        printf("\n\n\n***** DEBUGMODE function: readfile \n param: \n struct record** start\nchar filename[]: %s \n\n\n", filename);
    }
    file = fopen(filename, "r");
    invalid = 0;
    if (file == NULL)
    {
        invalid = -1;
    }
    else
    {
        while (fscanf(file, "%d,%[^,],%[^\n]\n", &accountno, name, address) == 3)
        {
            addRecord(start, accountno, name, address);
            invalid++;
        }
    }
    fclose(file);
    return invalid;
}

/*****************************************************************
//  Function name: cleanup
//
//  DESCRIPTION:   Called at the end of the function to clear up heap space
//                 
// 
//  Parameters:    struct record** start: the address of the first record  
// 
//  Return values:  0: No record under accountno
//                  uaccountno: account number that was deleted
//
***************************************************************/

void cleanup(struct record **start)
{
    struct record *temp;
    struct record *temp2;
    if (debugmode == 1)
    {
        printf("\n\n\n***** DEBUGMODE function: cleanup \n param: \n struct record* start \n\n\n");
    }
    temp = *start;
    temp2 = NULL;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    *start = NULL;
}
