//Name: Vince Bjazevic
//File: Count (iterative) CPP

#include "count_inversion_recursive.hpp"

int count_inversions_recursive(const std::vector<int>&numbers, int n) {
    if(n == 1) return 0;
    if(numbers[n] > numbers[n+1]){
        return 1+count_inversions_recursive(numbers, n-1);
    }
    else {
        return count_inversions_recursive(numbers, n-1);
    }
}
