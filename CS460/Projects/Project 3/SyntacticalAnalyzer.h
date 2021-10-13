/*******************************************************************************
* File name: SyntacticalAnalyzer.h                                             *
* Project: CS 460 Project 2 Fall 2020                                          *
* Author: Vince Bjazevic                                                       *
* Date: 10/30/2020                                                             *
* Description: This file contains                                              *
*******************************************************************************/

#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"
#include "CodeGenerator.h"

using namespace std;

class SyntacticalAnalyzer
{
public:
    SyntacticalAnalyzer (char * filename);
    ~SyntacticalAnalyzer ();

private:

    LexicalAnalyzer * lex;
    CodeGenerator * code;
    token_type token;
    int program();
    int more_defines();
    int define();
    int stmt_list(string last);
    int stmt(string last);
    int literal();
    int quoted_lit();
    int more_tokens();
    int param_list();
    int else_part();
    int stmt_pair();
    int stmt_pair_body();
    int assign_pair();
    int more_assigns();
    int action();
    int any_other_token(bool is_lit);
    ofstream lst;
    ofstream p2;
    ofstream dbg;
    bool is_main;
};

#endif