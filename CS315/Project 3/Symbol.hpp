#ifndef PROJECT1_SYMBOL_HPP
#define PROJECT1_SYMBOL_HPP
#include "Token.hpp"
#include "InfixToPostfix.hpp"
#include "Tokenizer.hpp"
#include "Numbers.hpp"
#include <map>
#include<vector>
#include <iostream>
#include <stack>

class Symbol {
public:
    bool find(char &character, std::vector<char> &index, std::vector<int> &value);
    int topValue(std::stack <int>&stack);
    int evaluateExpression(const std::vector<Token *> &exprTokens, std::vector<char> &index,std::vector<int> &values);
};


#endif //PROJECT1_SYMBOL_HPP
