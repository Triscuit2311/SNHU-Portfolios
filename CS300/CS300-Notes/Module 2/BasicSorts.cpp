
/*
Author: Dante A. Trisciuzzi
Date: September 2022
Description: Personal Code Notes for CS300 (DSA)
 .. Insertion, Selection, and Shell sort implementations
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


void insertionSort(vector<int>& nums){
    int j = 0;
    for(int i = 0; i < nums.size(); i++){
        j = i;
        while(j > 0 && nums[j] < nums[j - 1]){
            swap(nums[j], nums[j-1]);
            j--;
        }
    }
}

void selectionSort(vector<int> & nums){

    int nextSmallestIndex = 0;

    for(int i = 0; i < nums.size(); i++){

        nextSmallestIndex = i;

        for(int j = i; j < nums.size(); j++){
            if( nums[j] < nums[nextSmallestIndex]){
                nextSmallestIndex = j;
            }
        }

        if(i == nextSmallestIndex) continue;
        
        swap(nums[i], nums[nextSmallestIndex]);
    }
}

void insertionSortInterleaved(vector<int>& nums, int startindex, int gap){
    int j = 0;
    for(int i = startindex + gap; i < nums.size(); i += gap){
        j = i;
        while(j - gap >= startindex && nums[j] < nums[j - gap]){
            swap(nums[j], nums[j - gap]);
            j -= gap;
        }
    }
}

void ShellSort(vector<int> & nums){

    vector<int> gapValues = {1};

    int x = 2;
    while(x * 2 < nums.size()){
        x = x * 2 - 1;
        gapValues.push_back(x);
    }

    for(auto gap : gapValues)
        for(auto i = 0; i < gap; i++)
            insertionSortInterleaved(nums, i, gap);
}


int main(char* __argc, int __argv) {
    
    vector<int> nums = {2,5,17,18,1,3,15,7,22,9,10};

    for(auto n : nums)
        cout << n << " ";
    cout << endl;

    ShellSort(nums);

    for(auto n : nums)
        cout << n << " ";
    cout << endl;

    return 0;
}
