#include <iostream>
#include <utility>
#include "Tokenizer.hpp"
#include <stack>
Tokenizer::Tokenizer(std::string name):
        inputFileName{std::move(name)} {
    inputStream.open(inputFileName, std::ios::in);  // open the input file. We will make sure that it is open in getToken.
}

Token* Tokenizer::getToken() {
    char c;
    if (!inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }
    if(inputStream.peek() == EOF) {
        Token *token1 = new Token;
        token1->eof(true);
        token1->eol(true);
        return token1;
    }
    while (inputStream.get(c) && c ==' ' ) {}
    Token* token = new Token(c);
    if (inputStream.eof()) {
        token -> eof(true);
        return token;
    }
    if (c == '\n') {
        token->eol(true);
        return token;
    }

    if (c == 'X' || c == 'I' || c == 'V' || c == 'L' || c == 'M' || c == 'D' || c == 'C') {
        std::string roman = "";
        roman += c;
        while(inputStream.get(c) && (
                c == 'X' || c == 'I' || c == 'V' || c == 'L' || c == 'M' || c == 'D' || c == 'C'))
            roman += c;
        inputStream.unget();
        token ->romanNumber(roman);
        return token;
    }

    return token;
}

std::vector<Token*> Tokenizer::getExpresion(std::vector<char> &index) {
    while (expression.size()!=0)
        expression.pop_back();
    Token* token;
    token = getToken();
    if(token->eof()) {
        Token* token1 = new Token;
        token->eol(true);
       expression.push_back(token1);
        return expression;
    }
    if(token->eol()){
        while(token->eol()&&!token->eof())
            token = getToken();
    }
    if(!token->isAVariable()) {
            std::cout<<"MALFORMED EXPERSION: Missing variable";
            exit(3);
    }
    variable = token->getVariable();
    index.push_back(variable);
    token = getToken();
    if(!token->isEqualSign()) {
        std::cout<<"MALFORMED EXPERSION: Missing equal sign/got:";
        token->print();
        exit(3);
    }
    while(!token->eol() &&!token->eof()) {
        token = getToken();
        expression.push_back(token);
    }
    return expression;
}