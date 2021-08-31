//
// Created by student on 2019-12-04.
//


#ifndef PROJECT1_NUMBERS_HPP
#define PROJECT1_NUMBERS_HPP
#include<iostream>
#include "Tokenizer.hpp"
#include "Token.hpp"
#include<string>
#include <stack>

class Numbers {
public:
    int value(char romanDigit);
    int converterToDecimal(std::string &str);
    std::string convertToRoman(int &decimal);
    int evaluateExpression(const std::vector<Token *> &exprTokens );

};


#endif //PROJECT1_NUMBERS_HPP
