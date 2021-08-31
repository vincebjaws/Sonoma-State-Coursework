#include <iostream>
#include <iomanip>
#include "Pair.hpp"

Pair::Pair(std::string attributeName, std::string attributeValue):
                        _attributeName(attributeName), _attributeNumberValue(-1),
                        _attributeStringValue(attributeValue),
                        _isNumber(false), isID(false), isGPA(false)
                        {}

Pair::Pair(std::string attributeName, double num):
                        _attributeName(attributeName), _attributeStringValue(""),
                        _isNumber(true),  isID(false), isGPA(false),
                        _attributeNumberValue(num)
                        {}


bool Pair::isDouble() { return _isNumber; }
double Pair::numberValue() {return _attributeNumberValue; }
std::string Pair::stringValue() { return _attributeStringValue; }
std::string Pair::attributeName() { return _attributeName; }

void Pair::makePairAttributeName(std::string name) {
    _attributeName = name;
}

void Pair::makePairAttributeValue(std::string value) {
    _attributeStringValue = value;
}

void Pair::makePairAttributeNumber(double value) {
    _attributeNumberValue = value;
    _isNumber = true;
}

void Pair::printPair() {
    if(_isNumber) {
        //std::cout << "A pair containing a number value:"<<std::endl;
        std::cout << _attributeName << " : " << _attributeNumberValue << std::endl;
    }
    else {
        //std::cout << "A pair containing a string value:"<<std::endl;
        std::cout << _attributeName << " : " << _attributeStringValue << std::endl;
    }
}