#include <iomanip>
#include <cstdlib>
#include <map>
#include <cstring>
#include "LexicalAnalyzer.h"

using namespace std;

/***********************************************************************************************************************
 * Name: Vince Bjazevic
 * Project: Project 1 (460)
 * Date: Oct, 11, 2020
 * Description: This project takes in a DFA in the form of a transition table, and takes in an input of lexemes
 * in which the DFA parses, and names. Outputs to 3 seperate files, a debug file, a token file, a listing file.
 *
 **********************************************************************************************************************/

static const signed int table[14][24] = {
     //  0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23
     //Sta     c     a     d     r    alp    "     ?     _     +     -     .    num    /     *     =     >     <     (     )     [     ]     '    ws
        {0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0},
        {1,   10,    2,    2,    2,    2,    9,  -37,  -37,    3,    4,    5,    6,  -23,  -24,  -27,   12,   13,  -32,  -33,  -34,  -35,  -36,    1},
        {2,    2,    2,    2,    2,    2,   -1,   -1,    2,   -1,   -1,   -1,    2,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1},
        {3,  -21,  -21,  -21,  -21,  -21,  -21,  -21,  -21,  -21,  -21,    8,    6,  -21,  -21,  -21,  -21,  -21,  -21,  -21,  -21,  -21,  -21,  -21},
        {4,  -22,  -22,  -22,  -22,  -22,  -22,  -22,  -22,  -22,  -22,    8,    6,  -22,  -22,  -22,  -22,  -22,  -22,  -22,  -22,  -22,  -22,  -22},
        {5,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,    7,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37},
        {6,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,    7,    6,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2},
        {7,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,    7,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2},
        {8,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,    7,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37},
        {9,    9,    9,    9,    9,    9,   -3,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9},
        {10,   2,   11,   11,    2,    2,   -1,   -1,    2,   -1,   -1,   -1,    2,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1},
        {11,   2,    2,   11,   -4,    2,   -1,   -1,    2,   -1,   -1,   -1,    2,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1},
        {12, -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,   -30, -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28},
        {13, -29,  -29,  -29,  -29,  -29,  -29,  -29,  -29,  -29,  -29,  -29,  -29,  -29,  -29,   -31, -29,  -29,  -29,  -29,  -29,  -29 , -29,  -29},
};


LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	// This function will initialize the lexical analyzer class
	// Constructor
    int len = strlen(filename);
    string nameOfFile = filename;
    nameOfFile = nameOfFile.substr(0,len-3);
    endOfFile = false;
    linenum = pos = errors = 0;
    evalLine = lexeme = "";
    token = NONE;
    //Opens and checks each file
	input.open(filename);
    if(!input.is_open()){
        cout << "Unable to open " << filename << ".\nExiting..." << endl;
        exit(1);
    }
    listingFile << "Input file: " << filename  << endl;

    debugFile.open(nameOfFile + ".dbg");
    if(!debugFile.is_open()){
        cout << "Unable to open debug file" << ".\nExiting..." << endl;
        exit(1);
    }

    listingFile.open(nameOfFile + ".lst");
    if(!listingFile.is_open()){
        cout << "Unable to open listing file" << ".\nExiting..." << endl;
        exit(1);
    }

    tokenFile.open(nameOfFile + ".p1");
    if(!tokenFile.is_open()){
        cout << "Unable to open token file" << ".\nExiting..." << endl;
        exit(1);
    }

}

LexicalAnalyzer::~LexicalAnalyzer ()
{
    // This function will complete the execution of the lexical analyzer class
    // Deconstructor, also outs errors
    debugFile.close();
    listingFile.close();
    tokenFile.close();
	input.close();

    if (errors == 0){
        cout << "No errors found.";
    }
    else if(errors == 1){
        cout << "1 error found.";
    }
    else
        cout << errors << " errors found." << endl;

}

token_type LexicalAnalyzer::GetToken () {
    // This function will find the next lexeme int the input file and return
    // the token_type value associated with that lexeme

    // Inits variables
    token = NONE;
    int nextState = 0;
    int DFAstate = 1;
    int column = 0;
    char last_char;
    lexeme = "";
    int line_size = 0;

    if (pos == 0) {
        getline(input, evalLine);
        linenum = linenum + 1;
        listingFile << '\t' << linenum << ": " << evalLine << endl;
    }
    line_size = evalLine.size();

    if (line_size == 0) {
        if (!input.eof()){
            token = this->GetToken();
        }

        else {
            token = EOF_T;
            listingFile << '\t' << linenum+1 << ": " << endl;
            listingFile << errors << " errors found in input file" << endl;
        }
        return token;
    }
    for (int i = pos; i < evalLine.size(); i++) {

        if (isspace(evalLine[i]))
            column = 23;

        else if (isalpha(evalLine[i])) {
                if (evalLine[i] == 'c')
                    column = 1; // column for c
                else if (evalLine[i] == 'a')
                    column = 2; // column for a
                else if (evalLine[i] == 'd')
                    column = 3; // column for d
                else if (evalLine[i] == 'r') {
                    column = 4; // column for r
                }
                else{
                    column = 5;
                }
        } else if (isdigit(evalLine[i]))
            column = 12;

        else {
            if (evalLine[i] == '+') {
                column = 9;
            } else if (evalLine[i] == '(') {
                column = 18;
            } else if (evalLine[i] == '_') {
                column = 8;
            } else if (evalLine[i] == '-') {
                column = 10;
            } else if (evalLine[i] == '>') {
                column = 16;
            } else if (evalLine[i] == '?') {
                column = 7;
            } else if (evalLine[i] == '*') {
                column = 14;
            } else if (evalLine[i] == '/') {
                column = 13;
            } else if (evalLine[i] == '.') {
                column = 11;
            } else if (evalLine[i] == '<') {
                column = 17;
            } else if (evalLine[i] == '"') {
                column = 6;
            } else if (evalLine[i] == ')') {
                column = 19;
            } else if (evalLine[i] == '=') {
                column = 15;
            } else if (evalLine[i] == '[') {
                column = 20;
            } else if (evalLine[i] == ']') {
                column = 21;
            } else {
                column = 22;
            }
        }

        nextState = table[DFAstate][column];

        debugFile << "Evaluated char: " << evalLine[i] << " on line: " << linenum
                  << " from state: " << DFAstate << " to " << nextState << endl;

        if (nextState == 1 && DFAstate == 1 && column == 23) {

            pos++;
            token = this->GetToken();

            if (token == -37) {
                string errorMsg = "Error at " + to_string(linenum) + "'" + to_string(pos - 1) + ": Invalid char";
                if (lexeme == "+." || lexeme == "-.")
                    errorMsg += lexeme;
                else
                    errorMsg += evalLine[i];
                ReportError(errorMsg);
                errors++;
            }
            return token;
        }
        if (nextState != -37 || DFAstate == 1) {
            lexeme += evalLine[i];
        }


        if (nextState == -1) {
            if (lexeme != "string?" && lexeme != "number?" && lexeme != "zero?" &&
                lexeme != "list?" && lexeme != "null?") {
                lexeme.erase(lexeme.size() - 1);
                if (lexeme != "cons" && lexeme != "if" && lexeme != "cond" && lexeme != "else" &&
                    lexeme != "display" && lexeme != "newline" && lexeme != "and" && lexeme != "or" &&
                    lexeme != "not" && lexeme != "define" && lexeme != "modulo" && lexeme != "round")
                    token = IDENT_T;
                else if (lexeme == "cons")
                    token = CONS_T;
                else if (lexeme == "if")
                    token = IF_T;
                else if (lexeme == "cond")
                    token = COND_T;
                else if (lexeme == "else")
                    token = ELSE_T;
                else if (lexeme == "display")
                    token = DISPLAY_T;
                else if (lexeme == "newline")
                    token = NEWLINE_T;
                else if (lexeme == "and")
                    token = AND_T;
                else if (lexeme == "or")
                    token = OR_T;
                else if (lexeme == "not")
                    token = NOT_T;
                else if (lexeme == "define")
                    token = DEFINE_T;
                else if (lexeme == "modulo")
                    token = MODULO_T;
                else if (lexeme == "round")
                    token = ROUND_T;
            } else if (lexeme == "string?")
                token = STRINGP_T;
            else if (lexeme == "number?")
                token = NUMBERP_T;
            else if (lexeme == "list?")
                token = LISTP_T;
            else if (lexeme == "zero?")
                token = ZEROP_T;
            else if (lexeme == "null?")
                token = NULLP_T;

            pos = pos + lexeme.size();
            return token;
        }

        else if(nextState < 0){
            auto type = (token_type)nextState;
            pos = pos + lexeme.size();

            if(type == -37 || type == 8 || lexeme == "+." || lexeme == "-." || lexeme == ".")
            {
                errors++;
                string e_message = "";
                e_message = "Error at " + to_string(linenum) + "," + to_string(pos - 1) + ": Invalid character found: ";
                if (evalLine[i] == '.')
                    if(evalLine[i-1] == '+')
                        e_message.append("+.");// = e_message + "+.";
                    else if(evalLine[i-1] == '-')
                        e_message.append("-.");
                    else
                        e_message += evalLine[i];
                else
                    e_message += evalLine[i];
                ReportError(e_message);

            }return type;
        }
        DFAstate = nextState;
        last_char = evalLine[i];
    }

    if (line_size == pos) {
        if (!input.eof()) {
            pos = 0;
            token = this->GetToken();
        } else {
            token = EOF_T;
        }
        return token;
    }
    else if (input.eof() && DFAstate < 0){
        auto type = (token_type)DFAstate;
        endOfFile = true;
        return type;
        }
    else{
        auto type = (token_type)DFAstate;
        pos = 0;
        return type;
    }

}



string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it.
	if(t == 8){
        return "ERROR_T";
	}
    if(t == 2)
        return "IDENT_T";
	if(t == -37)
	    return "ERROR_T";
	if(t == -1)
        return "IDENT_T";
    if(t == -2)
        return "NUMLIT_T";
    if(t == -3)
        return "STRLIT_T";
    if(t == -4)
        return "LISTOP_T";
    if(t == -5)
        return "CONS_T";
    if(t == -6)
        return "IF_T";
    if(t == -7)
        return "COND_T";
    if(t == -8)
        return "ELSE_T";
    if(t == -9)
        return "DISPLAY_T";
    if(t == -10)
        return "NEWLINE_T";
    if(t == -11)
        return "AND_T";
    if(t == -12)
        return "OR_T";
    if(t == -13)
        return "NOT_T";
    if(t == -14)
        return "DEFINE_T";
    if(t == -15)
        return "LET_T";
    if(t == -16)
        return "NUMBERP_T";
    if(t == -17)
        return "LISTP_T";
    if(t == -18)
        return "ZEROP_T";
    if(t == -19)
        return "NULLP_T";
    if(t == -20)
        return "STRINGP_T";
    if(t == -21)
        return "PLUS_T";
    if(t == -22)
        return "MINUS_T";
    if(t == -23)
        return "DIV_T";
    if(t == -24)
        return "MULT_T";
    if(t == -25)
        return "MODULO_T";
    if(t == -26)
        return "ROUND_T";
    if(t == -27)
        return "EQUALTO_T";
    if(t == -28)
        return "GT_T";
    if(t == -29)
        return "LT_T";
    if(t == 12)
        return "GT_T";
    if(t == 13)
        return "LT_T";
    if(t == 16)
        return "GT_T";
    if(t == 17)
        return "LT_T";
    if(t == -30)
        return "GTE_T";
    if(t == -31)
        return "LTE_T";
    if(t == -32)
        return "LPAREN_T";
    if(t == -33)
        return "RPAREN_T";
    if(t == -34)
        return "LBRACK_T";
    if(t == -35)
        return "RBRACK_T";
    if(t == -36)
        return "SQUOTE_T";
    if(t == -38)
        return "EOF_T";
    return "CAN'T FIND NAME";
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return lexeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
    listingFile << msg << endl;
}
