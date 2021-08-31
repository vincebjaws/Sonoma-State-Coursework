#ifndef LAB01_2_TOKENIZER_HPP
#define LAB01_2_TOKENIZER_HPP


#include <string>
#include <fstream>
#include "Token.hpp"
#include "Symbol.hpp"
#include <vector>

class Tokenizer {

public:
    Tokenizer(std::string);
    Token* getToken();
    std::vector<Token *> getExpresion(std::vector<char> &index);
    char getVariable() {return variable;}

private:

    std::vector <Token *> expression;
    std::string inputFileName;
    std::ifstream inputStream;
    bool charOfInterest(char c);
    char variable;

};


#endif //LAB01_2_TOKENIZER_HPP
