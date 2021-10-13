#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
    //Outputs to token file
    int len = strlen(filename);
	lex = new LexicalAnalyzer (filename);
    string name = filename;
    name = name.substr(0, len-3);
    tokenFile.open(name + ".p1", fstream::app);
	token_type t;

	while ((t = lex->GetToken()) != EOF_T)
	{
	    if(t != '\''){
            tokenFile << '\t' << left << setw(16) << lex->GetTokenName(t) << lex->GetLexeme() << endl;
	    }
	}
	tokenFile << '\t' << left << lex->GetTokenName(t) << lex->GetLexeme() << endl;
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
