// NAME: Vince Bjazevic
// DATE DUE: 9/6/2019
// LAB 1 PHASE 1
// Tokenizer.cpp is a way of parsing through .html file and find valid tags



#include <iostream>
#include "Tokenizer.hpp"

Tokenizer::Tokenizer(std::string name): lineNumber{0},
                                        charPosition{-1},
                                        inputFileName{name} {
    inputStream.open(inputFileName, std::ios::in);  // open the input file. We will make sure that it is open in getToken.
}

bool Tokenizer::charOfInterest(char c) {
  if (c == '<' or c == '>') { // Finds < or > which is the first sign of a valid tag
      return true;
  }
  if (c == '/' && inputStream.peek() == '>') //checks "/" is leading into a tag
      return true;
  return false;
}
  
Token Tokenizer::getToken() {
    char c;

    if( ! inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }
    
    while( inputStream.get(c) && ! charOfInterest(c) ) {
        // keep track of the line number and the character position
            charPosition++;
        if (c == '\n')
            lineNumber++;
    }
    charPosition++;
    Token token(lineNumber, charPosition);
    if( inputStream.eof() ) {
        token.endOfFile() = true;
        return token;
    }
    if( c == '<' ) { // A possible open tag.
      std::string s = "";
      if (isalnum(inputStream.peek())) {
	token.isOpenTag() = true;
	while (inputStream.get(c) && isalnum(c)) {
	  s+= c;
	  charPosition++;
	}
	token.makeOpenTag(s);
	inputStream.unget(); // Ungets the the current char
	return token;
      }
      else if(inputStream.peek() == '/') {
	token.isCloseTag() = true;
	inputStream.get(c);
	s+= c;
	charPosition++; 
	  while (inputStream.get(c) && isalnum(c)) {
	    s += c; // Adds to tag name
	    charPosition++;
	  }
	  token.makeCloseTag(s);
	  inputStream.unget(); 
	  return token;
      }
    }
    else if( c == '>') {
      token.isCloseAngleBracket() = true;
      return token;
    }
    
    else if(c == '/') {
      inputStream.get(c);
      token.isCloseStandAloneTag() = true;
      return token;
    }

}
