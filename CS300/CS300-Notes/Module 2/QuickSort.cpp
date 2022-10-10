
/*
Author: Dante A. Trisciuzzi
Date: September 2022
Description: Personal Code Notes for CS300 (DSA)
.. My first quicksort implementation
*/


#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

template <class T>
void Swap(T& a, T& b) {
    T _t = a;
    a = b;
    b = _t;
}

int partition( vector<int>& nums, int lowIndex, int highIndex){

    int pivot = nums[lowIndex + (highIndex - lowIndex )/2];

    while(true){
        while(nums[lowIndex] < pivot) lowIndex++;
        while (nums[highIndex] > pivot) highIndex--;

        if(lowIndex >= highIndex) break;

        swap(nums[lowIndex], nums[highIndex]);

        lowIndex++;
        highIndex--;
    }
    return highIndex;
}

void quicksortInternal(vector<int> & nums, int lowIndex, int highIndex){
    if(lowIndex >= highIndex) return;
    auto lowEnd =  partition(nums, lowIndex, highIndex);
    quicksortInternal(nums, lowIndex, lowEnd);
    quicksortInternal(nums, lowEnd + 1, highIndex);
}

void Quicksort(vector<int> & nums){
    quicksortInternal(nums, 0, nums.size());
}


int main(char* __argc, int __argv) {
    
    vector<int> nums = {6, 82, 11, 28, 91, 0, 2, 7, 63, 54, 21, 14, 4, 5, 29, 82};

    for(auto n : nums)
        cout << n << " ";
    cout << endl;

    Quicksort(nums);


    for(auto n : nums)
        cout << n << " ";
    cout << endl;

    return 0;
}
