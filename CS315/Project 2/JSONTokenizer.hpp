#ifndef LAB01_2_TOKENIZER_HPP
#define LAB01_2_TOKENIZER_HPP


#include <string>
#include <fstream>
#include "JSONToken.hpp"
#include <vector>

class JSONTokenizer {

public:
    JSONTokenizer(std::string);
    JSONToken getToken();

private:

    std::string inputFileName;
    std::ifstream inputStream;
    bool charOfInterest(char c);

};


#endif //LAB01_2_TOKENIZER_HPP
