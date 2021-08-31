//Name: Vince Bjazevic
//File: left right (recursive) CPP

#include "largest_left_right_recursive.hpp"


int helper_left(int prev, int current, std::vector<int>numbers){ // left implementation of helper
    if(current==0) return 0;
    if(numbers[prev] > numbers[current]) return numbers[prev];
    else if(numbers[current] > numbers[prev] && prev == 0) return 0;
    return helper_left(prev-1, current,numbers);
}

int helper_right(int next, int current, std::vector<int>numbers){ // right implementation of helper
    if(current==numbers.size()) return 0;
    if(numbers[next] > numbers[current]) return numbers[next];
    else if(numbers[current] > numbers[next] && next == numbers.size()) return 0;
    return helper_right(next+1, current,numbers);
}


void largest_left_right_recursive(const std::vector<int> &numbers, std::vector<int> &result, int n) {
    int left = 0;
    int right = 0;
    if (n == 0) { // so left does not get called
        if(helper_right(n+1,n,numbers) <= numbers[n]) result.push_back(0);
        else result.push_back(helper_right(n+1, n, numbers));
        return;
    }

    else if(n == numbers.size()) { // so right does not get called
        largest_left_right_recursive(numbers, result, n - 1);
        if (helper_left(n - 1, n, numbers) <= numbers[n]) result.push_back(0);
        else result.push_back(helper_left(n - 1, n, numbers));
    }

    else { // compare left and right
        largest_left_right_recursive(numbers, result, n - 1);
        if (helper_left(n - 1, n, numbers) <= numbers[n]) left = 0;
        else left = helper_left(n - 1, n, numbers);
        if (helper_right(n + 1, n, numbers) <= numbers[n]) right = 0;
        else right = helper_right(n + 1, n, numbers);
        if(right>left) result.push_back(right);
        else result.push_back(left);
    }

   return;
}