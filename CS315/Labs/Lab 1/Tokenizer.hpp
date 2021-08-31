// NAME: Vince Bjazevic
// DATE DUE: 9/6/2019
// LAB 1 PHASE 1
// Tokenizer.hpp is a header file for Tokenizer.cpp

#ifndef LAB01_2_TOKENIZER_HPP
#define LAB01_2_TOKENIZER_HPP


#include <string>
#include <fstream>
#include "Token.hpp"

class Tokenizer {

public:
    Tokenizer(std::string);
    Token getToken();

private:
    int lineNumber, charPosition;
    std::string inputFileName;
    std::ifstream inputStream;

    bool charOfInterest(char c);
};


#endif //LAB01_2_TOKENIZER_HPP
