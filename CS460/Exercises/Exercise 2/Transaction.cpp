/*******************************************************************
*                                                                  *
* File: Transaction.cpp                                            *
* Written by: Ace Programmer                                       *
* Written on: November 2017                                        *
* Description: This file contains the implementation of the        *
*	transaction class described in the header file             *
*	Transaction.h.                                             *
*                                                                  *
*******************************************************************/

#include "Transaction.h"
#include <iomanip>
#include <cmath>

using namespace std;

#ifdef DEBUG
#define debug if (true) cout
#else
#define debug if (false) cout
#endif

/*******************************************************************
*                                                                  *
* Function: Transaction () is the defaut constructor for the       *
*	Transaction class.                                         *
*                                                                  *
*******************************************************************/

Transaction::Transaction ()
{
	amount = currency = coin = 0.0;
	dollars = halves = quarters = dimes = nickles = pennies = 0;
}

/*******************************************************************
*                                                                  *
* Function: Transaction (const Date & D) is an alternate           *
*	constructor for the Transaction class. A valid Date object *
*	should be passed to this constructor.                      *
*                                                                  *
*******************************************************************/

Transaction::Transaction (const Date & D)
{
	date = D;
	amount = currency = coin = 0.0;
	dollars = halves = quarters = dimes = nickles = pennies = 0;
}

/*******************************************************************
*                                                                  *
* Function: This function will return the date stored in the       *
*	 Transaction class object.                                 *
*                                                                  *
*******************************************************************/

Date & Transaction::TransDate ()
{
	return date;
}

/*******************************************************************
*                                                                  *
* Function: This function will return a Transaction object         *
*	containing data regarding the change given for a purchase. *
*                                                                  *
*******************************************************************/

Transaction Transaction::MakeChange (Transaction & bank)
{
	Transaction change (date);
	float tendered = currency + coin;
	if (tendered < amount || (tendered - amount > bank.coin))
	{
		change = *this;
		change.amount = tendered;
		return change;
	}
	int coin_conversion = static_cast<int>(amount*100);
	if ((bank.pennies == 0 && pennies == 0 && coin_conversion%2 != 0)) // Added a secondary safeguard that checks if bank
	                                                                   // or amount given has pennies and checks if i coin recived is odd
	                                                                    // so the amount never goes negative
    {
        change = *this;
        change.amount = tendered;
        return change;
    }
	bank += *this;
	bank.amount -= amount;
	bank.amount += tendered;
	debug << bank << endl;
	int difference = round((tendered - amount) * 100);  // Changed the difference so it would round, error came to one penny short
	change.dollars = difference / 100 > bank.dollars ? bank.dollars : difference / 100;
	difference -= change.dollars * 100;
	change.halves = difference / 50 > bank.halves ? bank.halves : difference / 50;
	difference -= change.halves * 50;
	change.quarters = difference / 25 > bank.quarters ? bank.quarters : difference / 25;
	difference -= change.quarters * 25;
	change.dimes = difference / 10 > bank.dimes ? bank.dimes : difference / 10;
	difference -= change.dimes * 10;
	change.nickles = difference / 5 > bank.nickles ? bank.nickles : difference / 5;
	difference -= change.nickles * 5;
	change.pennies = difference;
	change.coin = change.amount = tendered - amount;
	bank -= change;
	bank.TransDate() = date;
	debug << bank << endl;
	return change;
}

/*******************************************************************
*                                                                  *
* Function: This is the += operator for the Transaction class.     *
*                                                                  *
*******************************************************************/

Transaction Transaction::operator += (Transaction & T)
{
	amount += T.amount;
	currency += T.currency;
	coin += T.coin;
	dollars += T.dollars;
	halves += T.halves;
	quarters += T.quarters;
	dimes += T.dimes;
	nickles += T.nickles;
	pennies += T.pennies;
	return * this;
}

/*******************************************************************
*                                                                  *
* Function: This is the -= operator for the Transaction class.     *
*                                                                  *
*******************************************************************/

Transaction Transaction::operator -= (Transaction & T)
{
	amount -= T.amount;
	currency -= T.currency;
	coin -= T.coin;
	dollars -= T.dollars;
	halves -= T.halves;
	quarters -= T.quarters;
	dimes -= T.dimes;
	nickles -= T.nickles;
	pennies -= T.pennies;
	return * this;
}

/*******************************************************************
*                                                                  *
* Function: This is the input (extraction) operator for the	   *
*	Transaction class.                                         *
*                                                                  *
*******************************************************************/

istream & operator >> (istream & ins, Transaction & T)
{   

	ins >> T.date;
	ins >> T.amount >> T.currency;
	ins >> T.dollars >> T.halves >> T.quarters >> T.dimes >> T.nickles >> T.pennies;
	T.coin = T.dollars;
	T.coin += T.halves * 0.5;
	T.coin += T.quarters * 0.25;
	T.coin += T.dimes * 0.1;
	T.coin += T.nickles * 0.05;
	T.coin += T.pennies * 0.01;
	return ins;
}

/*******************************************************************
*                                                                  *
* Function: This is the output (insertion) operator for the        *
*	Transaction class.                                         *
*                                                                  *
*******************************************************************/

ostream & operator << (ostream & outs, const Transaction & T)
{
	outs << T.date;
	outs << setw (10) << fixed << setprecision (2) << T.amount;
	outs << setw (10) << fixed << setprecision (2) << T.currency;
	debug << setw (10) << fixed << setprecision (2) << T.coin;
	outs << setw (5) << T.dollars;
	outs << setw (5) << T.halves;
	outs << setw (5) << T.quarters;
	outs << setw (5) << T.dimes;
	outs << setw (5) << T.nickles;
	outs << setw (5) << T.pennies;
	return outs;
}

