#include <iostream>
#include <utility>
#include "JSONTokenizer.hpp"
#include <sstream>
#include <ctype.h>
#include <stack>
JSONTokenizer::JSONTokenizer(std::string name):
                                        inputFileName{std::move(name)} {
    inputStream.open(inputFileName, std::ios::in);  // open the input file. We will make sure that it is open in getToken.
}

bool JSONTokenizer::charOfInterest(char c) {
    if(c == '[' )
        return true;
    if(c == ']')
        return true;
    if(c == '{')
        return true;
    if(c == '}')
        return true;
    if(c == ':')
        return true;
    if(c == ',')
        return true;
    if(c == '"')
        return true;
    if(isdigit(c))
        return true;
   return false;
}

JSONToken JSONTokenizer::getToken() {
    char c;
    if (!inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }
    while (inputStream.get(c) && !charOfInterest(c)) {
        if (c == '\n') {
        }
    }
    JSONToken jsontoken;
    if (inputStream.eof()) {
        jsontoken.endOfFile() = true;
        return jsontoken;
    }
    if (c == '"') { // && inputStream.peek() != '/') { // A possible open tag.
        std::string tagName;
        jsontoken.isName() = true;
        while (isalnum(inputStream.peek()) && inputStream.get(c))
            tagName += c;
        inputStream.get(c);
        jsontoken.makeName(tagName);
        return jsontoken;
    }

    if (c == '[') {
        jsontoken.isOpenBracket() = true;
        return jsontoken;
    }
    if (c == ']') {
        jsontoken.isCloseBracket() = true;
        return jsontoken;
    }
    if (c == '{') {
        jsontoken.isOpenBrace() = true;
        return jsontoken;
    }
    if (c == '}') {
        jsontoken.isCloseBrace() = true;
        return jsontoken;
    }
    if (c == ':') {
        jsontoken.isColon() = true;
        return jsontoken;
    }
    if (c == ',') {
        jsontoken.isComma() = true;
        return jsontoken;
    }
    else {
        inputStream.putback(c);
        double value;
        inputStream >> value;
        jsontoken.isValue() = true;
        jsontoken.makeValue(value);
        return jsontoken;
    }
}
