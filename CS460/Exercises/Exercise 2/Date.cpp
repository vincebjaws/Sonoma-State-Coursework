/*******************************************************************
*                                                                  *
* File: Date.cpp                                                   *
* Written by: Ace Programmer                                       *
* Written on: November 2017                                        *
* Description: This file contains the implementation of the date   *
*	class described in the header file Date.h.                 *
*                                                                  *
*******************************************************************/

#include "Date.h"
#include <sstream>
#include <iomanip>
using namespace std;

#ifdef DEBUG
#define debug if (true) cout
#else
#define debug if (false) cout
#endif

/*******************************************************************
*                                                                  *
* Function: Date () is the defaut constructor for the Date class.  *
*                                                                  *
*******************************************************************/

Date::Date ()
{
	month = day = 1;
	year = 2017;
}

/*******************************************************************
*                                                                  *
* Function: Date (const string & D) is an alternate constructor    *
*	for the Date class. A string containing the date in m/d/y  *
*	format should be passed to this constructor.               *
*                                                                  *
*******************************************************************/

Date::Date (const string & D)
{
	debug << "String: " << D << endl;
	month = day = 1;
	year = 2017;
	stringstream ss (D);
	char slash;
	ss >> month >> slash >> day >> slash;
	string ys;
	ss >> ys;
	if (ys.length() && isdigit (ys[0])) {
        year = ys[0] != '2' ? 2000 + stoi(ys) : stoi(ys);
        if (year < 2016) // This is for any year put in as the form yy instead of yyyy
            year = year + 2000; // Adds 2000 to year for date cohesion
    }
	debug << "Date: " << *this << endl;
}	

/*******************************************************************
*                                                                  *
* Function: This is the input (extraction) operator for the Date   *
*       class.                                                     *
*                                                                  *
*******************************************************************/

istream & operator >> (istream & ins, Date & D)
{
	string SD;
	ins >> SD;
	if (ins.fail())
		return ins;
	D = Date (SD);
	return ins;
}

/*******************************************************************
*                                                                  *
* Function: This is the output (insertion) operator for the Date   *
*       class.                                                     *
*                                                                  *
*******************************************************************/

ostream & operator << (ostream & outs, const Date & D)
{
	outs << setw (2)  << setfill ('0') << D.month << '/';
	outs << setw (2)  << D.day << '/' << D.year;
	outs << setfill (' ');
	return outs;
}
