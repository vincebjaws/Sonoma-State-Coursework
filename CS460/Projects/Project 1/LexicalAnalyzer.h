#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>

using namespace std;

enum token_type {EOF_T = -38, ERROR_T = -37,SQUOTE_T = -36 ,RBRACK_T = -35, LBRACK_T = -34,
    RPAREN_T = -33, LPAREN_T = -32, LTE_T = -31, GTE_T = -30,LT_T = -29, GT_T = -28,
    EQUALTO_T = -27, ROUND_T = -26, MODULO_T = -25, MULT_T = -24, DIV_T = -23,
    MINUS_T = -22, PLUS_T = -21, STRINGP_T = -20, NULLP_T = -19, ZEROP_T = -18,
    LISTP_T = -17, NUMBERP_T = -16, LET_T = -15, DEFINE_T = -14, NOT_T = -13,
    OR_T = -12, AND_T = -11, NEWLINE_T = -10, DISPLAY_T = -9, ELSE_T = -8,
    COND_T = -7, IF_T = -6, CONS_T = -5, LISTOP_T = -4, STRLIT_T = -3,
    NUMLIT_T = -2, IDENT_T = -1, NONE = 0};

class LexicalAnalyzer 
{
    public:
	explicit LexicalAnalyzer (char * filename);
	~LexicalAnalyzer ();
	token_type GetToken ();
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError (const string & msg);
	ofstream debugFile;	// .dbg
private:
	ifstream input; 	// .ss 
	ofstream listingFile;	// .lst
	ofstream tokenFile;	// .p1
	token_type token;
	string evalLine;
	bool endOfFile;
	int linenum;
	int pos;
	string lexeme;
	int errors;
};
	
#endif
