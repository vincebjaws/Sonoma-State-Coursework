//Name: Vince Bjazevic
//File: Lab02 left header (iterative)

#ifndef LAB02_LEFT_RECURSIVE_HPP
#define LAB02_LEFT_RECURSIVE_HPP
#include <vector>
#include <string>
#include "read_input.hpp"

void largest_left_recursive(const std::vector<int> &numbers, std::vector<int> &result, int n);
int helper(int prev, int current, std::vector<int>temp_vec);


#endif //LAB02_LEFT_RECURSIVE_HPP