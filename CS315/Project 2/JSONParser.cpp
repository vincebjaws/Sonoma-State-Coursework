#include <iostream>
#include "JSONParser.hpp"
#include <map>
#include <vector>
#include <iomanip>
using namespace std;


JSONParser::JSONParser(JSONTokenizer &tokenizer): tokenizer{tokenizer} {}

EntityInstance JSONParser::parseJSONObject() {
    // parseJSONObject is responsible for parsing a JSON object. As such,
    // the first token is expected to be an open brace.
    JSONToken token = tokenizer.getToken();
    if( ! token.isOpenBrace() ) {
        std::cout << "Error: JSONParser::parseJSONObject: Expected an open brace, but found" << std::endl;
        token.print();
        std::cout << "Terminating..." << std::endl;
        exit(1);
    }
    EntityInstance instance;
    do {
        Pair pair = parseAPair();
        instance.addAttribute(pair);
        token = tokenizer.getToken();
    } while( token.isComma() );  // after having read a pair, we expect a comma
    // So, we didn't find a comma. Then, it must be a close brace.
    if( ! token.isCloseBrace() ) {
        std::cout << "Error: JSONParser::parseJSONObject: Expected an close brace, but found" << std::endl;
        token.print();
        std::cout << "Terminating..." << std::endl;
        exit(1);
    }
    return instance;
}
Pair JSONParser::parseAPair() {
    JSONToken token1 = tokenizer.getToken();
    JSONToken token2 = tokenizer.getToken();
    JSONToken token3 = tokenizer.getToken();
    if(token3.isValue()) {
        Pair newPair(token1.entityName(), token3.entityValue());
        return newPair;
    }
    else {
        Pair newPair(token1.entityName(), token3.entityName());
        return newPair;
    }
}


Entity JSONParser::parseJSONEntity() {
    JSONToken token = tokenizer.getToken();
    if( ! token.isOpenBracket() ) {
        std::cout << "Error: JSONParser::parseJSONEntity: Expected an open bracket, but found" << std::endl;
        token.print();
        std::cout << "Terminating..." << std::endl;
        exit(1);
    }
    Entity _entity;
    do {
        EntityInstance newInstance = parseJSONObject();
        _entity.addObject(newInstance);
        token = tokenizer.getToken();
    } while( token.isComma() );  // after having read a pair, we expect a comma
    // So, we didn't find a comma. Then, it must be a close brace.
    if( ! token.isCloseBracket() ) {
        std::cout << "Error: JSONParser::parseJSONEntity: Expected an close bracket, but found" << std::endl;
        token.print();
        std::cout << "Terminating..." << std::endl;
        exit(1);
    }
    return _entity;
}
