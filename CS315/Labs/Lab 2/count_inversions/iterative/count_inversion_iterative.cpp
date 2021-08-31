//Name: Vince Bjazevic
//File: Count inversions (iterative) CPP
//


#include "count_inversion_iterative.hpp"

int count_inversions_iterative(const std::vector<int>&numbers) {
    int total_inverts = 0; // set count to zero
    if (numbers.size() == 0||numbers.size() == 1) return 0; // if the vector contains only one element

    for(int i=0; i<numbers.size()-1;i++){ // compare current with next
        if(numbers[i]>numbers[i+1])
            total_inverts++;
    }
    return total_inverts; // return total
}


