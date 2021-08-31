#include "Token.hpp"
#include "InfixToPostfix.hpp"
#include "Tokenizer.hpp"
#include "Symbol.hpp"
#include<vector>
#include <iostream>

int main(int argc, char *argv[]) {
    std::vector<char> index;
    std::vector<int> values;
    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if( ! inputStream.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        exit(2);
    }
    inputStream.close();
    std::vector<Token *> tokens = std::vector<Token *>();
    Tokenizer tokenizer(argv[1]);
    Symbol table;
    Numbers numbers;
    int control = 1;
    while(control == 1)
    {
       tokens = tokenizer.getExpresion(index);
       int numTokens = tokens.size();
       if(numTokens != 1) {
           InfixToPostfix *itop = new InfixToPostfix();
           std::vector<Token *> postfixTokens;
           itop->convert(tokens, postfixTokens);
           int final = table.evaluateExpression(postfixTokens, index, values);
           values.push_back(final);
           std::string roman = numbers.convertToRoman(final);
       }
       else
           control = 0;
    }
    for(int i = 0; i < index.size();i++)
        std::cout<< index[i]<< " equals " << numbers.convertToRoman(values[i]) << std::endl;
    return 0;
}
