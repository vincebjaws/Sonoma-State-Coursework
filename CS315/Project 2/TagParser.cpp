#include <iostream>
#include "TagParser.hpp"
#include "Tokenizer.hpp"
#include "Token.hpp"
#include <map>
#include <vector>
#include <iomanip>
using namespace std;
TagParser::TagParser(std::string name): inputFileName{name} {}

void TagParser::parseSumTags() {
    Tokenizer tokenizer(inputFileName);
    Token token = tokenizer.getToken();
    while (!token.endOfFile()) {
        if (token.isOpenTag()) {
            handleOpenTag(tokenizer, token);
        }
        else if (token.isCloseTag())
            handleCloseTag(tokenizer, token);
        else if (token.isCloseAngleBracket() && possibleTagNames.size() == 0|| token.isOpenAngleBracket()  ) {
            token.print();
            std::cout << (token.isCloseAngleBracket() ? " :ignoring random close angle-bracket."
                                                      : " :ignoring random open angle-bracket.") << std::endl;
        } else {
            token.print();
            std::cout << " unknown token." << std::endl;
        }
        token = tokenizer.getToken();
    }
}

void TagParser::handleCloseTag(Tokenizer & tokenizer, Token & token) {
    Token nextToken = tokenizer.getToken();
    if(possibleTagNames.back().tagName() != token.tagName() || possibleTagNames.size() == 0){
        token.print();
        std::cout << " (with close angle bracket ";
        nextToken.print();
        std::cout <<") doesn't have a matching open tag, will discard it." << std::endl;
    }
        if(nextToken.isCloseAngleBracket()) {
            if (possibleTagNames.back().tagName() == token.tagName()) {
                buildMap(possibleTagNames.back(), token);
                possibleTagNames.pop_back();
            }
        }
    else {
        std::vector<Token> tempStack = possibleTagNames;
            string badTag = possibleTagNames[0].tagName();
        if (!(token.tagName() == badTag))


        std::cout << "</" <<token.tagName() <<  " closes while the following tags still remain open." << std::endl;
        for (auto itr=possibleTagNames.begin(); itr != possibleTagNames.end(); ++itr) {

            std::cout << std::setw(7);
            itr->print();
            std::cout << endl;
        }

    }

}

void TagParser::handleStandAloneCloseTag(Token token) {
    if(possibleTagNames.size() == 0) {
        std::cout << "We have entered into the handleStandAloneCloseTag case by mistake" << std::endl;
    }
        Token startToken = possibleTagNames.back();
        buildMap(startToken, token);
        possibleTagNames.pop_back();
}



void TagParser::printHappyMap() {

    std::cout << std::endl << "The following is a list of well formed HTML tags.\n" << std::endl;

    for (auto mapItr = goodTagNames.begin(); mapItr != goodTagNames.end(); ++mapItr) {
        std::vector<Token> locations = mapItr->second;

        std::string plural = "location.";

        if(locations.size() > 2) plural = "locations.";
        std::cout << mapItr -> first << " appeared in the following " << locations.size()/2 << " " << plural << std::endl;
        for (auto vItr = locations.begin(); vItr != locations.end(); ++vItr) {
           if(vItr->isOpenTag())  std::cout << std::setw(7);

           vItr->print();

           if(vItr->isOpenTag()) std::cout << " -- ";

           else if(vItr->isCloseTag() || vItr->isCloseStandAloneTag()) std::cout << std::endl;

        }
    }
}

void TagParser::buildMap(Token token, Token nextToken) {



    if (!checkMap(token.tagName())) {
        goodTagNames[token.tagName()] = std::vector<Token>();
    }

        goodTagNames[token.tagName()].push_back({token});
        goodTagNames[token.tagName()].push_back({nextToken});
        //std::cout << " Our map size is" << goodTagNames.size();
    }


    bool TagParser::checkMap(std::string tagName) {
        auto it = goodTagNames.find(tagName);
        return it != goodTagNames.end();
    }

void TagParser::handleOpenTag(Tokenizer & tokenizer, Token & token) {
    Token nextToken = tokenizer.getToken();
    if(token.tagName() == ""){
        std::cout << "We have entered into the open bracket case by mistake." << std::endl;
    }
    if(nextToken.isCloseAngleBracket() ) {
        possibleTagNames.push_back(token);
        return;
    }
    else if (nextToken.isCloseStandAloneTag() ) {
      buildMap(token, nextToken);
        return;
    }
    else{
        auto it = goodTagNames.find(token.tagName());
        if(it->first != token.tagName()) {
            vector<Token> myValue;
            goodTagNames[token.tagName()] = myValue;
            goodTagNames[token.tagName()].push_back(token);
        }
        token.print();
        std::cout  << " is missing a '>', or a '/>'. Will discard it." << std::endl;
        tokenizer.putback(token);
     }
 }

