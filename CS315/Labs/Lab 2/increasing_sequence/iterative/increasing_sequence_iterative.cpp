//Name: Vince Bjazevic
//File: Increasing (iterative) CPP
//

#include "increasing_sequence_iterative.hpp"

int increasing_sequence_iterative(const std::vector<int>&numbers) {
    int maximum = 0;
    int count = 1; // set to 1
    if (numbers.size() == 1) return 1; // case of size 1
    for(int i=0; i<numbers.size();i++){

        if(numbers[i]<=numbers[i+1]) count++; // compare current with next if true count++
        else {
            if (count > maximum) {
                maximum = count;
                count = 1; // refresh count
            }
            else count = 1; // refresh count
        }
    }
    return maximum;
}
