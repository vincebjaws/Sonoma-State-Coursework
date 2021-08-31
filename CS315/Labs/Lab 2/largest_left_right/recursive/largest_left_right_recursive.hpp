//Name: Vince Bjazevic
//File: Lab02 left header (iterative)

#ifndef LAB02_LEFT_RIGHT_HPP
#define LAB02_LEFT_RIGHT_HPP
#include <vector>
#include <string>
#include "read_input.hpp"

void largest_left_right_recursive(const std::vector<int> &numbers, std::vector<int> &result, int n);
int helper_left(int prev, int current, std::vector<int>temp_vec);
int helper_right(int prev, int current, std::vector<int>temp_vec);

#endif //LAB02_LEFT_RIGHT_HPP