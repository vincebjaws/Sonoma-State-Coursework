#include<iostream>
#include<string>

#ifndef TOKEN_HPP
#define TOKEN_HPP


class Token {

public:
    Token() { init(); }
    Token(char c) { init(); _symbol = c; }
    Token(const std::string s) { init(); _romanNumber = s; }

    std::string romanNumber() const     { return _romanNumber; }
    void romanNumber( std::string str ) { _romanNumber = str; }

    bool eof() const { return _eof; }
    void eof(bool v) { _eof = v;    }

    bool eol() const { return _eol; }
    void eol(bool v) { _eol = v;    }

    bool isOpenParen() const  { return _symbol == '('; }
    bool isCloseParen() const { return _symbol == ')'; }

    bool isEqualSign() const              { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; } 
    bool isAdditionOperator() const       { return _symbol == '+'; } 
    bool isSubtractionOperator() const    { return _symbol == '-'; } 
    bool isModuloOperator() const         { return _symbol == '%'; } 
    bool isDivisionOperator() const       { return _symbol == '/'; } 
    bool isAVariable() const              { return _symbol >= 'a' && _symbol <= 'z'; } 
    char getVariable() const              { return _symbol; }

    bool isRomanNumber() const { return _romanNumber.length() > 0; } 

    void print() const;

private:
    void init();  

    std::string _romanNumber;
    bool _eof, _eol;
    char _symbol;
};

#endif
