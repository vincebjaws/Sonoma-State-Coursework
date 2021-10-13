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
    code = new CodeGenerator (filename, lex);
    is_main = false;
    program();
}

SyntacticalAnalyzer::~SyntacticalAnalyzer() {
    delete lex;
    if (lst.is_open()|| p2.is_open() || dbg.is_open()) {
        if (lst.is_open()) lst.close();
        if (p2.is_open()) p2.close();
        if (dbg.is_open()) dbg.close();
    }
   delete code;
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
        total_errs += stmt_list("");
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
    is_main = false;
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

    if (lex->GetTokenName(token) ==  "IDENT_T") {
        string name = lex->GetLexeme();
        if(name == "main"){
            code->WriteCode(0, "\nint main ()\n");
            is_main = true;
        } else
            code->WriteCode(0, "Object " + name + "(");
        token = lex->GetToken();
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

    total_errs += param_list();
   code->WriteCode(0, "{\n"); // Beginning of a new function fix
   code->WriteCode(1, "Object __RetVal;\n"); //fix
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

    total_errs += stmt("");
    total_errs += stmt_list("");

    if (lex->GetTokenName(token) ==  "RPAREN_T") {
        if(is_main){
            code->WriteCode(0, ";\n");
            code->WriteCode(1, "return 0;\n");
        }
        else {
            code->WriteCode(1, "return __RetVal;\n");
        }
        code->WriteCode(0, "}\n");
        token = lex->GetToken();
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

int SyntacticalAnalyzer::stmt_list (string last){
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
        total_errs += stmt("");
        code->WriteCode(0, last);
        total_errs += stmt_list("");
    }
    return total_errs;
}

int SyntacticalAnalyzer::stmt (string last) {
    int total_errs = 0;

    if (lex->GetTokenName(token) ==  "IDENT_T"){
        p2 << "Using Rule 8" << endl;
        code->WriteCode(0, lex->GetLexeme());
        token = lex->GetToken();
        code->WriteCode(0, ";\n");
        return total_errs;
    }

    else if (lex->GetTokenName(token) == "LPAREN_T"){
        p2 << "Using Rule 9" << endl;
        token = lex->GetToken();
        total_errs += action();
            bool hit = false;  
        if (lex->GetTokenName(token) ==  "RPAREN_T") {
            token = lex->GetToken();
            if (lex->GetTokenName(token) ==  "LPAREN_T")
                if(last != "LISTOP")
                code->WriteCode(0, ";\n");
                hit = true;
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
        if (!hit)
            code->WriteCode(0, ";\n");
    }
    else if (lex->GetTokenName(token) == "EOF_T"){
        return total_errs;
    }

    else if (lex->GetTokenName(token) ==  "NUMLIT_T" || lex->GetTokenName(token) ==  "STRLIT_T"
    || lex->GetTokenName(token) ==  "SQUOTE_T"){
        p2 << "Using Rule 7" << endl;
        total_errs += literal();
        //code->WriteCode(0, ";\n");
    }
    else {
        string message = "'" + lex->GetLexeme() + "' unexpected";
        lex->ReportError(message);
        token = lex->GetToken();
        total_errs++;
        code->WriteCode(0, ";\n");
    }

    return total_errs;
}

int SyntacticalAnalyzer::literal (){
    int total_errs = 0;
    if (lex->GetTokenName(token) ==  "NUMLIT_T"){
        p2 << "Using Rule 10" << endl;
        code->WriteCode(0, "Object(" + lex->GetLexeme() + ")");
        token = lex->GetToken();
    }
    else if (lex->GetTokenName(token) ==  "STRLIT_T"){
        p2 << "Using Rule 11" << endl;
        code->WriteCode(0, "Object(" + lex->GetLexeme() + ")");
        token = lex->GetToken();
    }
    else if (lex->GetTokenName(token) ==  "SQUOTE_T"){
        p2 << "Using Rule 12" << endl;
        code->WriteCode(0, "Object(\"");
        token = lex->GetToken();

        total_errs += quoted_lit();
        code->WriteCode(0, "\")");
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
    total_errs += any_other_token(true);
    return total_errs;
}

int SyntacticalAnalyzer::more_tokens() {
    int total_errs = 0;
    if (lex->GetTokenName(token) ==  "RPAREN_T") {
        p2 << "Using Rule 15" << endl;
        code->WriteCode(0, ")");
        return total_errs;
    }
    else if (lex->GetTokenName(token) == "EOF_T") {
        return total_errs;
    }

    else {
        p2 << "Using Rule 14" << endl;
        total_errs += any_other_token(false);
        code->WriteCode(0, " ");
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
        code->WriteCode(0, "Object " + lex->GetLexeme());
        token = lex->GetToken();
        if(lex->GetTokenName(token) ==  "RPAREN_T") code->WriteCode(0, ", ");
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
    }
    else if (lex->GetTokenName(token) == "EOF_T") {
        return total_errs;
    }

    else {
        p2 << "Using Rule 18" << endl;
        code->WriteCode(0, ";\n");
        code->WriteCode(1, "}\n");
        code->WriteCode(1, "else\n");
        code->WriteCode(1, "{\n");
        code->WriteCode(1, "");
        total_errs += stmt("");
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
        total_errs += stmt("");
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
        total_errs += stmt("");
        code->WriteCode(0, ")\n");
        code->WriteCode(1, "{\n");
        code->WriteCode(1, "");
        total_errs += stmt("");
        code->WriteCode(0, ";\n");
        code->WriteCode(1, "}\n");
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
        if (lex->GetTokenName(token) == "RPAREN_T")
            code->WriteCode(1, "else\n     if(");
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

            total_errs += stmt("");

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
        code->WriteCode(1, "if(");
        p2 << "Using Rule 27" << endl;
        token = lex->GetToken();
        total_errs += stmt("");
        code->WriteCode(0, ")\n");
        code->WriteCode(1, "{\n");
        code->WriteCode(1, "");
        total_errs += stmt("");
        total_errs += else_part();
        code->WriteCode(0, ";\n");
        code->WriteCode(1, "}\n");
    } else if (tokenName == "COND_T") {
        token = lex->GetToken();
        p2 << "Using Rule 28" << endl;
        code->WriteCode(1, "if(");
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
        code->WriteCode(0, ";\n");
        return total_errs;
    } else if (tokenName == "NEWLINE_T") {
        code->WriteCode(1, "cout << endl");
        token = lex->GetToken();
        p2 << "Using Rule 53" << endl;
        return total_errs;
    } else if (tokenName == "DISPLAY_T") {
        code->WriteCode(1, "cout << ");
        p2 << "Using Rule 52" << endl;
        token = lex->GetToken();
        total_errs += stmt("");

        return total_errs;
    }
    //if(lex->GetTokenName(token) != "LISTOP1_T" && lex->GetTokenName(token) != "LISTOP2_T")
    // code->WriteCode(1, "__RetVal = ");
    if (tokenName == "LET_T") { //    else if (tokenName == "LET_T") {
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
            total_errs += stmt("");
            total_errs += stmt_list("");
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
        code->WriteCode(0, "listop (\"" + lex->GetLexeme() + "\", ");
        token = lex->GetToken();
        total_errs += stmt("LISTOP");
        code->WriteCode(0, ")");
    } else if (tokenName == "LISTOP2_T") {
        p2 << "Using Rule 31" << endl;
        code->WriteCode(0, "listop (\"" + lex->GetLexeme() + "\", ");
        token = lex->GetToken();
        total_errs += stmt("LISTOP");
        code->WriteCode(0, ", ");
        total_errs += stmt("LISTOP");
        code->WriteCode(0, ")");
    } else if (tokenName == "AND_T") {
        p2 << "Using Rule 32" << endl;
        token = lex->GetToken();
        code->WriteCode(0, "(");
        total_errs += stmt_list("&&");
        code->WriteCode(0, ")");
    } else if (tokenName == "OR_T") {
        p2 << "Using Rule 33" << endl;
        code->WriteCode(0, "(");
        token = lex->GetToken();
        total_errs += stmt_list("||");
        code->WriteCode(0, ")");
    } else if (tokenName == "NOT_T") {
        p2 << "Using Rule 34" << endl;
        token = lex->GetToken();
        total_errs += stmt("");
    } else if (tokenName == "NUMBERP_T") {
        p2 << "Using Rule 35" << endl;
        token = lex->GetToken();
        total_errs += stmt("");
    } else if (tokenName == "LISTP_T") {
        p2 << "Using Rule 36" << endl;
        token = lex->GetToken();
        total_errs += stmt("");
    } else if (tokenName == "ZEROP_T") {
        p2 << "Using Rule 37" << endl;
        token = lex->GetToken();
        total_errs += stmt("");
    } else if (tokenName == "NULLP_T") {
        p2 << "Using Rule 38" << endl;
        token = lex->GetToken();
        total_errs += stmt("");
    } else if (tokenName == "STRINGP_T") {
        p2 << "Using Rule 39" << endl;
        token = lex->GetToken();
        total_errs += stmt("");
    } else if (tokenName == "PLUS_T") {
        code->WriteCode(0, "(");
        p2 << "Using Rule 40" << endl;
        token = lex->GetToken();
        total_errs += stmt_list(" + ");
        //code->WriteCode(0, "+");
        code->WriteCode(0, ")");
    } else if (tokenName == "MINUS_T") {
        p2 << "Using Rule 41" << endl;
        code->WriteCode(0, "(");
        token = lex->GetToken();
       // total_errs += stmt("");
        total_errs += stmt_list(" - ");
        code->WriteCode(0, ")");
    } else if (tokenName == "DIV_T") {
        code->WriteCode(0, "(");
        p2 << "Using Rule 42" << endl;
        token = lex->GetToken();
       // total_errs += stmt("");
        total_errs += stmt_list(" / ");
        code->WriteCode(0, ")");
    } else if (tokenName == "MULT_T") {
        code->WriteCode(0, "(");
        p2 << "Using Rule 43" << endl;
        token = lex->GetToken();
        total_errs += stmt_list(" * ");
        code->WriteCode(0, ")");
    } else if (tokenName == "MODULO_T") {
        code->WriteCode(0, "(");
        p2 << "Using Rule 44" << endl;
        token = lex->GetToken();
        //total_errs += stmt("");
        //total_errs += stmt("");
        total_errs += stmt_list(" % ");
        code->WriteCode(0, ")");
    } else if (tokenName == "ROUND_T") {
        p2 << "Using Rule 45" << endl;
        token = lex->GetToken();
        total_errs += stmt("");
    } else if (tokenName == "EQUALTO_T") {
        code->WriteCode(0, "(");
        p2 << "Using Rule 46" << endl;
        token = lex->GetToken();
        total_errs += stmt_list(" == ");
        code->WriteCode(0, ")");
    } else if (tokenName == "GT_T") {
        code->WriteCode(0, "(");
        p2 << "Using Rule 47" << endl;
        token = lex->GetToken();
        total_errs += stmt_list(" > ");
        code->WriteCode(0, ")");
    } else if (tokenName == "LT_T") {
        code->WriteCode(0, "(");
        p2 << "Using Rule 48" << endl;
        token = lex->GetToken();
        total_errs += stmt_list(" < ");
        code->WriteCode(0, ")");
    } else if (tokenName == "GTE_T") {
        code->WriteCode(0, "(");
        p2 << "Using Rule 49" << endl;
        token = lex->GetToken();
        total_errs += stmt_list(" >= ");
        code->WriteCode(0, ")");
    } else if (tokenName == "LTE_T") {
        code->WriteCode(0, "(");
        p2 << "Using Rule 50" << endl;
        token = lex->GetToken();
        total_errs += stmt_list(" <= "  );
        code->WriteCode(0, ")");
    } else if (tokenName == "IDENT_T") {
        code->WriteCode(0, lex->GetLexeme() + "(");
        p2 << "Using Rule 51" << endl;
        token = lex->GetToken();
        total_errs += stmt_list("");
        code->WriteCode(0, ")");
    } else if (tokenName == "NEWLINE_T") {
        p2 << "Using Rule 53" << endl;
        token = lex->GetToken();
    }
    return total_errs;
}

int SyntacticalAnalyzer::any_other_token(bool is_lit) {
    int total_errs = 0;

    string tokenName = lex->GetTokenName(token);
    char quote_check = lex->GetLexeme()[0];
    int ascii =  int(quote_check);
    string quote_remover = lex->GetLexeme();
    if(ascii == 39){
        quote_remover.erase (quote_remover.begin()+0);
    }
    else if(quote_check != '"') //&& ascii != 39)
        code->WriteCode(0, lex->GetLexeme());
    else{
        quote_remover.erase (quote_remover.begin()+0);
        quote_remover.erase (quote_remover.begin()+quote_remover.length()-1);
        code->WriteCode(0, quote_remover);
    }

    if (tokenName == "LPAREN_T") {
       // code->WriteCode(0, lex->GetLexeme());
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
        //code->WriteCode(0, lex->GetLexeme());
        p2 << "Using Rule 55" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "NUMLIT_T") {
     //   code->WriteCode(0, lex->GetLexeme());
        p2 << "Using Rule 56" << endl;
        token = lex->GetToken();
    }
    else if (tokenName == "STRLIT_T") {
      // code->WriteCode(0, lex->GetLexeme());
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
        total_errs += any_other_token(true);
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