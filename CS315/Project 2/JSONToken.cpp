#include <iostream>
#include <iomanip>
#include "JSONToken.hpp"

JSONToken::JSONToken(): _isOpenBrace(false),
                                 _isCloseBrace(false),
                                 _isColon(false),
                                 _isComma(false),
                                 _isCloseBracket(false),
                                 _isOpenBracket(false),
                                 _eof(false),
                                 _isValue(false),
                                 _isName(false)
                                 {}

bool &JSONToken::isOpenBrace() { return _isOpenBrace; }
bool &JSONToken::isCloseBrace() { return _isCloseBrace; }
bool &JSONToken::isCloseBracket() { return _isCloseBracket; }
bool &JSONToken::isOpenBracket() { return _isOpenBracket; }
bool &JSONToken::endOfFile() { return _eof; }
bool &JSONToken::isColon() { return _isColon; }
bool &JSONToken::isComma() { return _isComma; }
bool &JSONToken::isValue() {return _isValue; }
bool &JSONToken::isName() {return _isName; }
std::string JSONToken::entityName() { return _entityName; }
double JSONToken::entityValue() { return _entityValue; }

void JSONToken::makeName(std::string name) {
    _entityName = name;
    isName() = true;
}

void JSONToken::makeValue(double value) {
    _entityValue = value;
    isValue() = true;
}

void JSONToken::print() {

    if(isOpenBracket()) {
        std::cout << "[" << std::endl;
    } else if(isCloseBracket()) {
        std::cout << "]" << std::endl;
    } else if(isCloseBrace()) {
        std::cout << "}" << std::endl;
    } else if(isOpenBrace()) {
        std::cout << "{" << std::endl;
    } else if(isColon()) {
        std::cout << ":" << std::endl;
    } else if(isComma()) {
        std::cout << "," << std::endl;
    } else if(isValue()) {
            std::cout << _entityValue << std::endl;
    } else if(isName()) {
        std::cout << _entityName << std::endl;
    } else if(endOfFile()){
        std::cout << "End of file read...." << std::endl;
    }
    else
        std::cout << "Unkown" << std::endl;
}