//Name: Vince Bjazevic
//File: Main CPP

#include<iostream>
#include<string>
#include<vector>

#include "read_input.hpp"
#include "count_inversion_iterative.hpp"

int main(int argc, char *argv[]) {
  if(argc!=2) {
    std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
    exit(2);
  }
  std::vector<int> numbers;
  read_numbers(std::string(argv[1]), numbers);
  int result = count_inversions_iterative(numbers);
  std::cout << result << std::endl;

}

