/*******************************************************************
*                                                                  *
* File: simulator.cpp                                              *
* Written by: Ace Programmer                                       *
* Written on: November 2017                                        *
* Description: This file contains the main function for the change *
*	machine simulator program.                                 *
*                                                                  *
*******************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Transaction.h"
using namespace std;

#ifdef DEBUG
#define debug if (true) cout
#else
#define debug if (false) cout
#endif

void Heading (ostream & outs, const string & label);

/*******************************************************************
*                                                                  *
* Function: main (int argc, char * argv []) the main function for  *
*	the simulator.                                             *
*                                                                  *
*******************************************************************/

int main (int argc, char * argv [])
{
	if (argc < 2)
	{
		cout << "Usage: " << argv[0] << " <filename>\n";
		return 1;
	}
	ifstream data (argv[1]);
	if (data.fail())
	{
		cout << "Data file: " << argv[1] << " cannot be opened.\n";
		return 2;
	}

	Transaction bank, oneT, change;
	data >> bank;
	Transaction save, total (bank.TransDate()), returned (bank.TransDate());
	save = bank;
	Heading (cout, "Details\t");
	cout << "Starting bank:\n\t" << bank << endl;
	while (data >> oneT)
	{
		cout << "This transaction:\n\t" << oneT << endl;
		total += oneT;
		change = oneT.MakeChange (bank);
		returned += change;
		cout << "Change returned:\n\t" << change << endl;
		cout << "Current bank:\n\t" << bank << endl;
	}
	cout << "Ending bank:\n\t" << bank << endl;

	cout << endl;
	Heading (cout, "Summary   ");
	cout << "Starting  " << save << endl;
	cout << "Total     " << total << endl;
	cout << "Returned  " << returned << endl;
	cout << "Ending    " << bank << endl;
	
	return 0;
}

/*******************************************************************
*                                                                  *
* Function: Heading (ostream & outs, const string & label) will    *
*	print the column headers for the reports generated by this *
*	simulator.                                                 *
*                                                                  *
*******************************************************************/

void Heading (ostream & outs, const string & label)
{
	outs << label << "Date      ";
	outs << setw (10) << "Amount";
	outs << setw (10) << "Bills";
	debug << setw (10) << "Coin";
	outs << setw (5) << "$1";
	outs << setw (5) << ".50";
	outs << setw (5) << ".25";
	outs << setw (5) << ".10";
	outs << setw (5) << ".05";
	outs << setw (5) << ".01";
	outs << endl;
}
