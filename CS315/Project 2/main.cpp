#include <iostream>
#include "JSONTokenizer.hpp"
#include "JSONParser.hpp"
#include "JSONToken.hpp"


int main(int argc, char *argv[]) {
    std::ifstream inputStream;
    std::ifstream inputStream1;
    inputStream.open(argv[1], std::ios::in);    // open for reading
    inputStream1.open(argv[2], std::ios::in);    // open for reading
    if( ! inputStream.is_open() || ! inputStream1.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        std::cout << "Unable to open " << argv[2] << ". Terminating...";
        exit(2);
    }
    inputStream.close();
    inputStream1.close();
    JSONTokenizer jsonTokenizer(argv[1]); // The Tokenizer opens and reads from the input file..
    JSONTokenizer jsonTokenizer1(argv[2]);
    JSONParser parser(jsonTokenizer);
    JSONParser parser1(jsonTokenizer1);
    Entity prev =  parser.parseJSONEntity();
    Entity curr = parser1.parseJSONEntity();
    Entity intersect = prev.intersection(curr);
    intersect.createMatrix();
    return 0;
}
