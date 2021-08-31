//Name: Vince Bjazevic
//File: Main CPP

#include<iostream>
#include<string>
#include<vector>

#include "read_input.hpp"
#include "largest_left_recursive.hpp"

int main(int argc, char *argv[]) {
    if(argc!=2) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        exit(2);
    }
    std::vector<int> numbers, output;
    read_numbers(std::string(argv[1]), numbers);
    largest_left_recursive(numbers, output, numbers.size()-1);
    for(auto iter: output){
        std::cout << iter << std::endl;
    }

    return 0;
}