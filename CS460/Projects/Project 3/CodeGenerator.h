// Project: CS 460 Fall 2020 Project 3
// File: CodeGenerator.h
// Author: Dr. Watts
// Desciption: Code Generator class for Scheme to C++ translation

#ifndef CG_H
#define CG_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

class CodeGenerator 
{
    public:
	CodeGenerator (string filename, LexicalAnalyzer * L);
	~CodeGenerator ();
	void WriteCode (int tabs, string code);
    private:
	LexicalAnalyzer * lex;
	ofstream cpp;
};
	
#endif
