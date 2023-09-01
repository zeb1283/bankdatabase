/*****************************************************************
//  NAME:        Zeb Lakey
//
//  HOMEWORK:    Project 1
// 
//   CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        March 24, 2023
//
//  FILE:        user_interface.c
//
//   DESCRIPTION:
//   Contains main method that takes the general user input and
//   stores values in different variables, and getaddress that
//   obtains the user address
//
***************************************************************/

#include <stdio.h>
#include <string.h>
#include "database.h"
void getaddress(char[], int);
int debugmode;

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
    struct record * start = NULL;
    char command[20];
    int i;
    char name[20];
    char nums[30];
    int accountno;
    char address[50];
    int terminate;
    int numargs;
    terminate = 0;
    debugmode = 0;
    accountno = 0;
    if (argc == 2 && strcmp(argv[1], "debug") == 0)
    {
        debugmode = 1;
        printf("\n****** Now entering debug mode for homework3.\n\n");
    }
    else if (argc == 1)
    {
    }
    else
    {
        terminate = 1;
        printf("Please enter either ./homework3 or ./homework3 debug. (Error A)\n");
    }
    if (terminate == 0)
    {
        numargs = readfile(&start, "save.txt");
        if (debugmode == 1)
        {
            printf("\n\n\n ***DEBUG MODE*** Number of nodes developed from file: %d\n\n\n", numargs);
        }
        i = 0;
        printf("Hello! This is a program that mimics a bank database\n\n");
        printf("Please choose a menu option:\nadd: Add a new record in the database\nprintall: Print all records in database\nfind: Find record(s) within a specific account #\ndelete: Delete existing record(s) from the database using the account # as a key\nquit: quit the program\n\n");
        while (i == 0)
        {
            accountno = 0;
            printf("Please enter a command: ");
            fgets(command, 30, stdin);
            if (strncmp("add", command, strlen(command)-1) == 0)
            {
                printf("You have selected add.\n");
                printf("Please enter an account number: ");
                fgets(nums, 30, stdin);
                while (sscanf(nums, "%d", &accountno) != 1 || accountno <= 0)
                {
                    printf("Please enter a positive integer.(Error B)");
                    fgets(nums, 30, stdin);
                }
                printf("Please enter your name: ");
                fgets(name, 30, stdin);
                name[strlen(name)-1] = '\0';
                getaddress(address, 0);
                printf("Record has been added.\n");
                addRecord(&start, accountno, name, address);
                accountno = 0;
            }
            else if (strncmp("printall", command, strlen(command)-1) == 0)
            {
                printAllRecords(start);
                printf("\n Records printed. If nothing was printed here, no records are in the database.\n");
            }
            else if (strncmp("find", command, strlen(command)-1) == 0)
            {
                accountno = 0;
                printf("Please enter an account number you would like to find the record for: ");
                fgets(nums, 30, stdin);
                while (sscanf(nums, "%d", &accountno) != 1 || accountno <= 0)
                {
                    printf("Please enter a positive integer.");
                    fgets(nums, 30, stdin);
                }
                numargs = findRecord(start, accountno);
                if (numargs >= 0)
                {
                    printf("\n%d record(s) found!\n", numargs);
                }
                else
                {
                    printf("\nNo record found under this account number.\n");
                }
            }
            else if (strncmp("delete", command, strlen(command)-1) == 0)
            {
                accountno = 0;
                printf("Please enter an account number to delete: ");
                fgets(nums, 30, stdin);
                while (sscanf(nums, "%d", &accountno) != 1 || accountno <= 0)
                {
                    printf("Please enter a positive integer.(Error B)");
                    fgets(nums, 30, stdin);
                }
                printf("Account number input complete.\n");
                numargs = deleteRecord(&start, accountno);
                if (numargs >= 0)
                {
                    printf("\n%d record(s) deleted!\n", numargs);
                }
                else
                {
                    printf("\nNo record found under this account number.\n");
                }
            }
            else if (strncmp("quit", command, strlen(command)-1) == 0)
            {
                printf("\nquitting\n");
                i = 1;
                numargs = writefile(start, "save.txt");
                if (debugmode == 1)
                {
                    printf("\n\n\n ***DEBUG MODE*** Number of nodes written to file: %d\n\n\n", numargs);
                }
            }
            else
            {
                printf("Erroneous input, please press enter to try again");
                while (getchar() != '\n');
            }
        }
    }
    cleanup(&start);
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
    if (debugmode == 1)
    {
        printf("\n\n\n****** debugmode FUNCTION: getaddress\n address[] %s\n length %d\n\n\n", address, length);
    }
    printf("Please enter your address\n");
    printf("Press enter twice when done entering address.\n");
    /* Got idea on how to do this loop from a mix of docs explaining how to use fgetc and how int to character conversion works. Basically mishmashed a bunch of stuff into my own*/
    while (loop == 0 && (character = fgetc(stdin)) != EOF)
    {
        if (character == '\n')
        {
            if (i > 0 && address[i-1] == '\n')
            {
                loop = 1;
                address[i-1] = '\0';
            }
        }
        address[i++] = (char)character;
        length++;
        if (length == 49)
        {
            loop = 1;
            while (getchar() != '\n');
            printf("Address input too long, added up to the 49th character");
            address[i-1] = '\0';
        }
    }
    printf("Address input complete.\n");
}
