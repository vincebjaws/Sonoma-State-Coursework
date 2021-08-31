//Name: Vince Bjazevic
//File: left (iterative) CPP

#include "largest_left_recursive.hpp"

void largest_left_recursive(const std::vector<int> &numbers, std::vector<int> &result, int n) {
    if (n == 0) { // size 0 base case
        result.push_back(0);
        return;
    }
    else {
        largest_left_recursive(numbers, result, n - 1); // recursive call
        if(helper(n-1,n,numbers) <= numbers[n]) result.push_back(0);
        else result.push_back(helper(n-1, n, numbers)); // add to results
    }
    return;
}

int helper(int prev, int current, std::vector<int>numbers){ // helper

    if(current == 0) return 0;
    if(numbers[prev] > numbers[current]) return numbers[prev];
    else if(numbers[current] > numbers[prev] && prev == 0) return 0;
    return helper(prev-1, current,numbers);
}