//Vince Bjazevic
//
//

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "read_input.hpp"

void read_numbers(std::string filename, std::vector<int>& numbers) {

    std::ifstream inputFile(filename,std::fstream::in);
    int holder;
    while (inputFile>>holder) {
        numbers.push_back(holder);
    }
}