// NAME: Vince Bjazevic
// DATE DUE: 9/6/2019
// LAB 1 PHASE 1
// Token.hpp is a header file for Token.cpp

#ifndef LAB01_2_TOKEN_HPP
#define LAB01_2_TOKEN_HPP


#include <string>

class Token {
public:
    Token(int, int);
    bool &isOpenTag();
    bool &isCloseTag();

    bool &isCloseAngleBracket();

    bool &endOfFile();
    bool &isCloseStandAloneTag();

    std::string tagName();

    void makeOpenTag(std::string);
    void makeCloseTag(std::string);
    void print();

private:
    bool _isOpenTag, _isCloseTag, _isCloseAngleBracket,
        _eof, _isCloseStandAloneTag;

    std::string _tagName;
    int _lineNumber, _charPos;
};


#endif //LAB01_2_TOKEN_HPP
