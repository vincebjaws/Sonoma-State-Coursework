/*******************************************************************************
* File name: SyntacticalAnalyzer.cpp                                           *
* Project: CS 460 Project 2 Fall 2020                                          *
* Author: Vince Bjazevic                                                       *
* Date: 10/30/2020                                                             *
* Description: This file contains the syntactical analyzer                     *
*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename) {

    string fname(filename);
    fname.erase(fname.size() - 3);

    string DBGname = fname;
    string LSTname = fname;
    string P2name = fname;

    DBGname.append(".dbg");
    LSTname.append(".lst");
    P2name.append(".P2");

    lst.open(LSTname, std::ofstream::out);
    p2.open(P2name, std::ofstream::out);
    dbg.open(DBGname, std::ofstream::out);

    if (!lst.is_open()||!p2.is_open() || !dbg.is_open()) {
        if (!lst.is_open()) dbg << "Error opening " << LSTname << endl;
        if (!p2.is_open()) dbg << "Error opening " << P2name << endl;
        if (!dbg.is_open()) cout << "Error opening " << DBGname << endl;
        exit(1);
    }

    string message = "Input file: " + string(filename);
    lst << message << endl;

    lex = new LexicalAnalyzer(filename);
    program();
}

SyntacticalAnalyzer::~SyntacticalAnalyzer() {
    delete lex;
    if (lst.is_open()|| p2.is_open() || dbg.is_open()) {
        if (lst.is_open()) lst.close();
        if (p2.is_open()) p2.close();
        if (dbg.is_open()) dbg.close();
    }
}

int SyntacticalAnalyzer::program() {
    p2 << "Using Rule 1" << endl;
    int total_errs = 0;
    token = lex->GetToken();
    if (lex->GetTokenName(token) ==  "LPAREN_T")
        token = lex->GetToken();

    else if(lex->GetTokenName(token) == "EOF_T"){
        total_errs++;
        lex->ReportError("Unexpected end of file... Exiting.");
        return total_errs;
    }
    else {
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
        if(lex->GetTokenName(token) == "EOF_T"){
            return total_errs;
        }
        else{
            message = "'end of file' expected";
            lex->ReportError(message);
            return total_errs;
        }
    }
    total_errs += define();
    if (lex->GetTokenName(token) ==  "LPAREN_T")
        token = lex->GetToken();
    else {
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }
    total_errs += more_defines();
    if (lex->GetTokenName(token) ==  "EOF_T")
        token = lex->GetToken();
    else {
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }
    return total_errs;
}

int SyntacticalAnalyzer::more_defines() {
    int total_errs = 0;
    if(lex->GetTokenName(token) == "DEFINE_T"){
        p2 << "Using Rule 2" << endl;
        total_errs += define();
        if (lex->GetTokenName(token) ==  "LPAREN_T")
            token = lex->GetToken();
        else if (lex->GetTokenName(token) == "EOF_T"){
            return total_errs;
        }
        else{
            string message = "'" + lex->GetLexeme() + "' unexpected";
            lex->ReportError(message);
            token = lex->GetToken();
            total_errs++;
        }
        total_errs += more_defines();
    }
    if (lex->GetTokenName(token) ==  "IDENT_T"){
        p2 << "Using Rule 3" << endl;
        token = lex->GetToken();
        total_errs += stmt_list();
        if (lex->GetTokenName(token) ==  "RPAREN_T")
            token = lex->GetToken();

        else if (lex->GetTokenName(token) == "EOF_T")
            return total_errs;
        else
        {
            string message = "'" + lex->GetLexeme() + "' unexpected";
            lex->ReportError(message);
            token = lex->GetToken();
            total_errs++;
        }
    } else {
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }
    return total_errs;
}

int SyntacticalAnalyzer::define(){
    p2 << "Using Rule 4" << endl;
    int total_errs = 0;
    if (lex->GetTokenName(token) ==  "DEFINE_T")
        token = lex->GetToken();
    else if (lex->GetTokenName(token) == "EOF_T"){
        return total_errs;
    }
    else{
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }

    if (lex->GetTokenName(token) ==  "LPAREN_T")
        token = lex->GetToken();

    else if (lex->GetTokenName(token) == "EOF_T"){
        return total_errs;
    }

    else{
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }

    if (lex->GetTokenName(token) ==  "IDENT_T")
        token = lex->GetToken();

    else if (lex->GetTokenName(token) == "EOF_T"){
        return total_errs;
    }

    else{
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }

    total_errs += param_list();

    if (lex->GetTokenName(token) ==  "RPAREN_T")
        token = lex->GetToken();

    else if (lex->GetTokenName(token) == "EOF_T"){
        return total_errs;
    }

    else{
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }

    total_errs += stmt();
    total_errs += stmt_list();

    if (lex->GetTokenName(token) ==  "RPAREN_T")
        token = lex->GetToken();

    else if (lex->GetTokenName(token) == "EOF_T"){
        return total_errs;
    }

    else{
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }
    return total_errs;
}

int SyntacticalAnalyzer::stmt_list (){
    int total_errs = 0;

    if (lex->GetTokenName(token) ==  "RPAREN_T"){
        p2 << "Using Rule 6" << endl;
        return total_errs;
    }
    else if (lex->GetTokenName(token) == "EOF_T"){
        return total_errs;
    }

    else{
        p2 << "Using Rule 5" << endl;
        total_errs += stmt();
        total_errs += stmt_list();
    }
    return total_errs;
}

int SyntacticalAnalyzer::stmt () {
    int total_errs = 0;

    if (lex->GetTokenName(token) ==  "IDENT_T"){
        p2 << "Using Rule 8" << endl;
        token = lex->GetToken();
        return total_errs;
    }

    else if (lex->GetTokenName(token) == "LPAREN_T"){
        p2 << "Using Rule 9" << endl;
        token = lex->GetToken();
        total_errs += action();
        if (lex->GetTokenName(token) ==  "RPAREN_T")
            token = lex->GetToken();

        else if (lex->GetTokenName(token) == "EOF_T"){
            return total_errs;
        }

        else{
            string message = "'" + lex->GetLexeme() + "' unexpected";
            lex->ReportError(message);
            token = lex->GetToken();
            total_errs++;
        }
    }
    else if (lex->GetTokenName(token) == "EOF_T"){
        return total_errs;
    }

    else if (lex->GetTokenName(token) ==  "NUMLIT_T" || lex->GetTokenName(token) ==  "STRLIT_T"
    || lex->GetTokenName(token) ==  "SQUOTE_T"){
        p2 << "Using Rule 7" << endl;
        total_errs += literal();
    }
    else {
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }

    return total_errs;
}

int SyntacticalAnalyzer::literal (){
    int total_errs = 0;
    if (lex->GetTokenName(token) ==  "NUMLIT_T"){
        p2 << "Using Rule 10" << endl;
        token = lex->GetToken();
    }
    else if (lex->GetTokenName(token) ==  "STRLIT_T"){
        p2 << "Using Rule 11" << endl;
        token = lex->GetToken();
    }
    else if (lex->GetTokenName(token) ==  "SQUOTE_T"){
        p2 << "Using Rule 12" << endl;
        token = lex->GetToken();
        total_errs += quoted_lit();
    }

    else if (lex->GetTokenName(token) == "EOF_T"){
        return total_errs;
    }

    else{
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }
    return total_errs;
}

int SyntacticalAnalyzer::quoted_lit() {
    int total_errs = 0;
    p2 << "Using Rule 13" << endl;
    total_errs += any_other_token();
    return total_errs;
}

int SyntacticalAnalyzer::more_tokens() {
    int total_errs = 0;
    if (lex->GetTokenName(token) ==  "RPAREN_T") {
        p2 << "Using Rule 15" << endl;
        return total_errs;
    }
    else if (lex->GetTokenName(token) == "EOF_T") {
        return total_errs;
    }

    else {
        p2 << "Using Rule 14" << endl;
        total_errs += any_other_token();
        total_errs += more_tokens();
    }
    return total_errs;
}

int SyntacticalAnalyzer::param_list() {
    int total_errs = 0;
    if (lex->GetTokenName(token) ==  "RPAREN_T") {
        p2 << "Using Rule 17" << endl;
        return total_errs;
    }
    else if (lex->GetTokenName(token) == "IDENT_T") {
        p2 << "Using Rule 16" << endl;
        token = lex->GetToken();
        total_errs += param_list();
    }
    else if (lex->GetTokenName(token) == "EOF_T") {
        return total_errs;
    }
    else {
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }
    return total_errs;
}

int SyntacticalAnalyzer::else_part() {
    int total_errs = 0;
    if (lex->GetTokenName(token) ==  "RPAREN_T") {
        p2 << "Using Rule 19" << endl;
        return total_errs;
    }
    else if (lex->GetTokenName(token) == "EOF_T") {
        return total_errs;
    }

    else {
        p2 << "Using Rule 18" << endl;
        total_errs += stmt();
    }
    return total_errs;
}

int SyntacticalAnalyzer::stmt_pair() {
    int total_errs = 0;
    if (lex->GetTokenName(token) ==  "RPAREN_T") {
        p2 << "Using Rule 21" << endl;
        return total_errs;
    }
    else if (lex->GetTokenName(token) == "LPAREN_T") {
        p2 << "Using Rule 20" << endl;
        token = lex->GetToken();

        total_errs += stmt_pair_body();
    }
    else if (lex->GetTokenName(token) == "EOF_T") {
        return total_errs;
    }
    else {
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }
    return total_errs;
}

int SyntacticalAnalyzer::stmt_pair_body() {
    int total_errs = 0;
    if (lex->GetTokenName(token) == "ELSE_T") {
        token = lex->GetToken();
        p2 << "Using Rule 23" << endl;
        total_errs += stmt();
        if (lex->GetTokenName(token) == "RPAREN_T")
            token = lex->GetToken();
        else if (lex->GetTokenName(token) == "EOF_T"){
            return total_errs;
        }

        else{
            string message = "'" + lex->GetLexeme() + "' unexpected";
            lex->ReportError(message);
            token = lex->GetToken();
            total_errs++;
        }
    }
    else{
        p2 << "Using Rule 22" << endl;
        total_errs += stmt();
        total_errs += stmt();
        if (lex->GetTokenName(token) == "RPAREN_T")
            token = lex->GetToken();
        else if (lex->GetTokenName(token) == "EOF_T"){
            return total_errs;
        }

        else{
            string message = "'" + lex->GetLexeme() + "' unexpected";
            lex->ReportError(message);
            token = lex->GetToken();
            total_errs++;
        }
        total_errs += stmt_pair();
    }
    return total_errs;
}

int SyntacticalAnalyzer::assign_pair(){
    int total_errs = 0;
    string tokenName = lex->GetTokenName(token);

    if(tokenName == "LBRACK_T"){
        token = lex->GetToken();

        p2 << "Using Rule 24" << endl;

        if(lex->GetTokenName(token) == "IDENT_T"){
            token = lex->GetToken();

            total_errs += stmt();

            if (lex->GetTokenName(token) == "RBRACK_T")
                token = lex->GetToken();
            else if(lex->GetTokenName(token) == "EOF_T") {
                return total_errs;
            }
            else{
                total_errs++;
            }
        }

        else if(lex->GetTokenName(token) == "EOF_T") return total_errs;
        else{
            string message = "'" + lex->GetLexeme() + "' unexpected";
            lex->ReportError(message);
            token = lex->GetToken();
            total_errs++;
        }
    }

    else if(lex->GetTokenName(token) == "EOF_T")
        return total_errs;
    else{

        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }

    return total_errs;
}

int SyntacticalAnalyzer::more_assigns(){
    int total_errs = 0;
    string tokenName = lex->GetTokenName(token);

    if(tokenName == "RPAREN_T") {
        p2 << "Using Rule 26" << endl;
        return total_errs;
    }
    else if(lex->GetTokenName(token) == "EOF_T")
        return total_errs;

    p2 << "Using Rule 25" << endl;
    total_errs += assign_pair();
    total_errs +=  more_assigns();
    return total_errs;
}

int SyntacticalAnalyzer::action () {
    int total_errs = 0;
    string tokenName = lex->GetTokenName(token);
    if (tokenName == "IF_T") {
        p2 << "Using Rule 27" << endl;
        token = lex->GetToken();
        total_errs += stmt();
        total_errs += stmt();
        total_errs += else_part();
    } else if (tokenName == "COND_T") {
        token = lex->GetToken();
        p2 << "Using Rule 28" << endl;
        if (lex->GetTokenName(token) == "LPAREN_T") {
            token = lex->GetToken();
            total_errs += stmt_pair_body();
        } else if (lex->GetTokenName(token) == "EOF_T") {
            return total_errs;
        } else {
            string message = "'" + lex->GetLexeme() + "' unexpected";
            lex->ReportError(message);
            token = lex->GetToken();
            total_errs++;
        }
        return total_errs;
    } else if (tokenName == "NEWLINE_T") {
        token = lex->GetToken();
        p2 << "Using Rule 53" << endl;
        return total_errs;
    } else if (tokenName == "LET_T") {
        token = lex->GetToken();
        p2 << "Using Rule 29" << endl;
        if (lex->GetTokenName(token) == "LPAREN_T") {
            token = lex->GetToken();
        } else {
            string message = "'" + lex->GetLexeme() + "' unexpected";
            lex->ReportError(message);
            token = lex->GetToken();
            total_errs++;
        }
        total_errs += more_assigns();

        if (lex->GetTokenName(token) == "RPAREN_T") {
            token = lex->GetToken();
            total_errs += stmt();
            total_errs += stmt_list();
        } else if (lex->GetTokenName(token) == "EOF_T") {
            return total_errs;
        } else {
            string message = "'" + lex->GetLexeme() + "' unexpected";
            lex->ReportError(message);
            token = lex->GetToken();
            total_errs++;
        }
    } else if (tokenName == "LISTOP1_T") {
        p2 << "Using Rule 30" << endl;
        token = lex->GetToken();
        total_errs += stmt();
    } else if (tokenName == "LISTOP2_T") {
        p2 << "Using Rule 31" << endl;
        token = lex->GetToken();
        total_errs += stmt();
        total_errs += stmt();
    } else if (tokenName == "AND_T") {
        p2 << "Using Rule 32" << endl;
        token = lex->GetToken();
        total_errs += stmt_list();
    } else if (tokenName == "OR_T") {
        p2 << "Using Rule 33" << endl;
        token = lex->GetToken();
        total_errs += stmt_list();
    } else if (tokenName == "NOT_T") {
        p2 << "Using Rule 34" << endl;
        token = lex->GetToken();
        total_errs += stmt();
    } else if (tokenName == "NUMBERP_T") {
        p2 << "Using Rule 35" << endl;
        token = lex->GetToken();
        total_errs += stmt();
    } else if (tokenName == "LISTP_T") {
        p2 << "Using Rule 36" << endl;
        token = lex->GetToken();
        total_errs += stmt();
    } else if (tokenName == "ZEROP_T") {
        p2 << "Using Rule 37" << endl;
        token = lex->GetToken();
        total_errs += stmt();
    } else if (tokenName == "NULLP_T") {
        p2 << "Using Rule 38" << endl;
        token = lex->GetToken();
        total_errs += stmt();
    } else if (tokenName == "STRINGP_T") {
        p2 << "Using Rule 39" << endl;
        token = lex->GetToken();
        total_errs += stmt();
    } else if (tokenName == "PLUS_T") {
        p2 << "Using Rule 40" << endl;
        token = lex->GetToken();
        total_errs += stmt_list();
    } else if (tokenName == "MINUS_T") {
        p2 << "Using Rule 41" << endl;
        token = lex->GetToken();
        total_errs += stmt();
        total_errs += stmt_list();
    } else if (tokenName == "DIV_T") {
        p2 << "Using Rule 42" << endl;
        token = lex->GetToken();
        total_errs += stmt();
        total_errs += stmt_list();
    } else if (tokenName == "MULT_T") {
        p2 << "Using Rule 43" << endl;
        token = lex->GetToken();
        total_errs += stmt_list();
    } else if (tokenName == "MODULO_T") {
        p2 << "Using Rule 44" << endl;
        token = lex->GetToken();
        total_errs += stmt();
        total_errs += stmt();
    } else if (tokenName == "ROUND_T") {
        p2 << "Using Rule 45" << endl;
        token = lex->GetToken();
        total_errs += stmt();
    } else if (tokenName == "EQUALTO_T") {
        p2 << "Using Rule 46" << endl;
        token = lex->GetToken();
        total_errs += stmt_list();
    } else if (tokenName == "GT_T") {
        p2 << "Using Rule 47" << endl;
        token = lex->GetToken();
        total_errs += stmt_list();
    } else if (tokenName == "LT_T") {
        p2 << "Using Rule 48" << endl;
        token = lex->GetToken();
        total_errs += stmt_list();
    } else if (tokenName == "GTE_T") {
        p2 << "Using Rule 49" << endl;
        token = lex->GetToken();
        total_errs += stmt_list();
    } else if (tokenName == "LTE_T") {
        p2 << "Using Rule 50" << endl;
        token = lex->GetToken();
        total_errs += stmt_list();
    } else if (tokenName == "IDENT_T") {
        p2 << "Using Rule 51" << endl;
        token = lex->GetToken();
        total_errs += stmt_list();
    } else if (tokenName == "DISPLAY_T") {
        p2 << "Using Rule 52" << endl;
        token = lex->GetToken();
        total_errs += stmt();
    } else if (tokenName == "NEWLINE_T") {
        p2 << "Using Rule 53" << endl;
        token = lex->GetToken();
    }
    return total_errs;
}

int SyntacticalAnalyzer::any_other_token() {
    int total_errs = 0;
    string tokenName = lex->GetTokenName(token);
    if (tokenName == "LPAREN_T") {
        p2 << "Using Rule 54" << endl;
        token = lex->GetToken();
        total_errs += more_tokens();
        if (lex->GetTokenName(token) == "RPAREN_T")
            token = lex->GetToken();
        else {
            string message = "'" + lex->GetLexeme() + "' unexpected";
            lex->ReportError(message);
            token = lex->GetToken();
            total_errs++;
        }
    }
    else if (tokenName == "IDENT_T") {
        p2 << "Using Rule 55" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "NUMLIT_T") {
        p2 << "Using Rule 56" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "STRLIT_T") {
        p2 << "Using Rule 57" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "IF_T") {
        p2 << "Using Rule 58" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "DISPLAY_T") {
        p2 << "Using Rule 59" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "NEWLINE_T") {
        p2 << "Using Rule 60" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "LISTOP1_T") {
        p2 << "Using Rule 61" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "LISTOP2_T") {
        p2 << "Using Rule 62" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "AND_T") {
        p2 << "Using Rule 63" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "OR_T") {
        p2 << "Using Rule 64" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "NOT_T") {
        p2 << "Using Rule 65" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "DEFINE_T") {
        p2 << "Using Rule 66" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "LET_T") {
        p2 << "Using Rule 67" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "NUMBERP_T") {
        p2 << "Using Rule 68" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "LISTP_T") {
        p2 << "Using Rule 69" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "ZEROP_T") {
        p2 << "Using Rule 70" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "NULLP_T") {
        p2 << "Using Rule 71" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "STRINGP_T") {
        p2 << "Using Rule 72" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "PLUS_T") {
        p2 << "Using Rule 73" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "MINUS_T") {
        p2 << "Using Rule 74" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "DIV_T") {
        p2 << "Using Rule 75" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "MULT_T") {
        p2 << "Using Rule 76" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "MODULO_T") {
        p2 << "Using Rule 77" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "ROUND_T") {
        p2 << "Using Rule 78" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "EQUALTO_T") {
        p2 << "Using Rule 79" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "GT_T") {
        p2 << "Using Rule 80" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "LT_T") {
        p2 << "Using Rule 81" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "GTE_T") {
        p2 << "Using Rule 82" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "LTE_T") {
        p2 << "Using Rule 83" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "SQUOTE_T")
    {
        p2 << "Using Rule 84" << endl;
        token = lex->GetToken();
        total_errs += any_other_token();
    }
    else if (tokenName == "COND_T") {
        p2 << "Using Rule 85" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "ELSE_T") {
        p2 << "Using Rule 86" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "EOF_T") {
        p2 << "Reached end of file" << endl;
        return total_errs;
    }
    else {
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
    }
    return total_errs;
}