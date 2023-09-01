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
//  FILE:        database.h
//
//  DESCRIPTION:
//  All of the function prototypes that will be used in the
//  database.c file.
//
//
****************************************************************/
#include "record.h"
void addRecord(struct record**, int, char[], char[]);
void printAllRecords(struct record*);
int findRecord(struct record*,int);
int deleteRecord(struct record**, int);
int writefile(struct record *, char []);
int readfile(struct record **, char []);
void cleanup(struct record **);
