//Vince Bjazevic
//File: left right (iterative) CPP
//
#include "largest_left_right_iterative.hpp"

void largest_left_right_iterative(vector<int>& numbers, vector<int> &result){
    int left = 0; // create left int to hold greatest value
    int right = 0; // create right int to hold greatest value
    for(int i = 0; i<numbers.size(); i++) {
        left = helper_left(numbers, i);
        right = helper_right(numbers, i);
        if(left>right) // compare
            result.push_back(left);
        else
            result.push_back(right);
    }
}

int helper_left(vector<int> &helperVec, int n) { // helper for left
    for (int i = n -1; i>= 0;i--){
        if(helperVec[i] > helperVec[n]){
            return  helperVec[i];
        }
    }
    return 0;
}


int helper_right(vector<int> &helperVec, int n) { // helper for right
    for (int i = n+1; i < helperVec.size();i++){
        if(helperVec[i] > helperVec[n]){
            return  helperVec[i];
        }
    }
    return 0;
}
