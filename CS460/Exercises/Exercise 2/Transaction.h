#pragma once

/*******************************************************************
*                                                                  *
* File: Transaction.h                                              *
* Written by: Ace Programmer                                       *
* Written on: November 2017                                        *
* Description: This file contains the description of a transaction *
*	class.                                                     *
*                                                                  *
*******************************************************************/

#include <iostream>
#include "Date.h"
using namespace std;

class Transaction
{
    public:
	Transaction ();
	Transaction (const Date & D);
	Date & TransDate ();
	Transaction MakeChange (Transaction & bank);
	Transaction operator += (Transaction & T);
	Transaction operator -= (Transaction & T);
	friend istream & operator >> (istream & ins, Transaction & T);
	friend ostream & operator << (ostream & outs, const Transaction & T); 
    private:
	Date date;
	float amount, currency, coin;
	int dollars, halves, quarters, dimes, nickles, pennies;
};
