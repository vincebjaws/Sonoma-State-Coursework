/*******************************************************************
*                                                                  *
* File: Date.h                                                     *
* Written by: Ace Programmer                                       *
* Written on: November 2017                                        *
* Description: This file contains the description of a date class. *
*                                                                  *
*******************************************************************/

#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;

class Date
{
    public:
	Date ();
	Date (const string & D);
	friend istream & operator >> (istream & ins, Date & D);
	friend ostream & operator << (ostream & outs, const Date & D); 
    private:
	int month, day, year;
};

#endif
