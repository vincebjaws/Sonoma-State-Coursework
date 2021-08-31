//Vince Bjazevic
//File: left (iterative) CPP
//
#include "largest_left_iterative.hpp"

void largest_left_iterative(vector<int>& numbers, vector<int> &result){
    for(int i = 0; i<numbers.size(); i++) { //iterate
        result.push_back(helper(numbers, i)); // use helper
    }
}

int helper(vector<int> &helperVec, int n) { // helper function
    for (int i = n -1; i>= 0;i--){
        if(helperVec[i] > helperVec[n]) return helperVec[i]; // compare
    }
    return 0;
}