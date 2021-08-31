//Name: Vince Bjazevic
//File: Lab02 count inversions header (iterative)

#ifndef LAB02_COUNT_INVERSION_HPP
#define LAB02_COUNT_INVERSION_HPP
#include <vector>
#include <string>

using namespace std;
int helper_left(vector<int> &helperVec, int n);
int helper_right(vector<int> &helperVec, int n);
void largest_left_right_iterative(vector<int>& numbers, vector<int> &result);

#endif //LAB02_COUNT_INVERSION_HPP

