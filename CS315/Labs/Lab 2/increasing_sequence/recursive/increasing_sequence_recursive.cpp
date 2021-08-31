//Name: Vince Bjazevic
//File: Count (iterative) CPP

#include "increasing_sequence_recursive.hpp"

int increasing_sequence_recursive(std::vector<int> &numbers, int startIdx) {
    if(n == 1) return 0;
    if(numbers[n] > numbers[n+1]){
        return 1+count_inversions_recursive(numbers, n-1);
    }
    else {
        return count_inversions_recursive(numbers, n-1);
    }
}
