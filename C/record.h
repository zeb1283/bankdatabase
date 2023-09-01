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
//  FILE:        record.h
//
//  DESCRIPTION:
//  Defines a structure that includes the account number, name
//  address, and a pointer referring to the next record 
//
//
****************************************************************/

struct record
{
    int accountno;
    char name[30];
    char address[50];
    struct record* next;
};
