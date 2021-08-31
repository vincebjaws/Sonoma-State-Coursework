#ifndef MISC_PAIR_HPP
#define MISC_PAIR_HPP
#include "JSONTokenizer.hpp"
#include "JSONToken.hpp"

class Pair { // represents a single attribute and its value:

public:
    Pair(std::string attributeName, std::string attributeValue);
    Pair(std::string attributeName, double);
    bool isDouble();  // is the datatype of the value of this attribute a double?
    double numberValue();
    std::string stringValue();
    std::string attributeName();
    void makePairAttributeName(std::string);
    void makePairAttributeValue(std::string);
    void makePairAttributeNumber(double);
    void printPair();

private:
    std::string _attributeName, _attributeStringValue;
    double _attributeNumberValue;
    bool _isNumber, isID, isGPA;
};


#endif //MISC_PAIR_HPP
