//
// Created by Ali A. Kooshesh on 8/21/18.
//

#ifndef LAB01_2_TOKEN_HPP
#define LAB01_2_TOKEN_HPP


#include <string>

class JSONToken {
public:
    JSONToken();
    bool &isOpenBrace();
    bool &isCloseBrace();
    bool &isOpenBracket();
    bool &isCloseBracket();
    bool &endOfFile();
    bool &isColon();
    bool &isComma();
    std::string entityName();
    double entityValue();
    bool &isValue();
    bool &isName();
    void makeValue(double);
    void makeName(std::string);
    void print();

private:
    bool _isOpenBrace, _isCloseBrace, _isCloseBracket,
        _eof, _isOpenBracket, _isColon, _isComma,
        _isValue, _isName;

    std::string _entityName;

    double _entityValue;

};


#endif //LAB01_2_TOKEN_HPP
