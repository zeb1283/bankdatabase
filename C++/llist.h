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
//  FILE:        llist.h
//
//  DESCRIPTION: Header file for llist class
//
***************************************************************/

#include "record.h"
#ifndef LLIST_H
#define LLIST_H

class llist
{
    private:
        record *    start;
        char        filename[20];
        int         readfile();
        int         writefile();
        void        cleanup();

    public:
        llist();
        llist(char[]);
        ~llist();
        void addRecord(int, char [ ],char [ ]);
        int findRecord(int);
        void printAllRecords();
        int deleteRecord(int);
};

#endif
