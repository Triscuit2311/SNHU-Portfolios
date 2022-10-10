
/*
Author: Dante A. Trisciuzzi
Date: September 2022
Description: Personal Code Notes for CS300 (DSA)
*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int factorial(int n){
    if(n==1)
        return 1;
    return n * factorial(n-1);
}

void TestFactorial(){
    cout << factorial(1) << endl;
    cout << factorial(10) << endl;
    cout << factorial(100) << endl;
}

int summation(int n){
    if(n==0)
        return 0;
    return n + summation(n-1);
}

void TestSum(){
    cout << summation(0) <<endl;
    cout << summation(10) <<endl;
    cout << summation(100) <<endl;
}


template <class T>
void reverseVector(std::vector<T> &vec, int startIndex, int endIndex){
    if(startIndex >= endIndex)
        return;
    T temp = vec.at(startIndex);
    vec.at(startIndex) = vec.at(endIndex);
    vec.at(endIndex) = temp;
    reverseVector(vec, startIndex + 1, endIndex-1);
}

void TestReverse(){
    std::vector<int> v(10);
    for(int i = 0; i<10;i++)
        v.at(i)=i;
    
    reverseVector(v, 0, 9);


    for(auto& n : v)
        cout << n << " ";
    cout << endl;
}

int FibonacciNumber(int n){
    if(n<=1) return n;
    return FibonacciNumber(n-1) + FibonacciNumber(n-2);
}

void TestFibo(){
    cout << FibonacciNumber(0) << endl;
    cout << FibonacciNumber(4) << endl;
    cout << FibonacciNumber(8) << endl;
    cout << FibonacciNumber(12) << endl;
}


int BinarySearch(vector<int> &vec, int num, int start, int end){
    if(start > end) return -1;
    int mid = start + (end-start)/2;
    if(vec.at(mid) == num)
        return mid;
    if(vec.at(mid) > num)
        return BinarySearch(vec, num, start, mid - 1);
    if(vec.at(mid) < num)
        return BinarySearch(vec, num, mid + 1, end);
}

void TestBinSearch(){
    std::vector<int> v(100);
    for(int i = 0; i<100;i++)
        v.at(i)=i;
    
    cout << BinarySearch(v,50,0,99) << endl;
    cout << BinarySearch(v,8,0,99) << endl;
    cout << BinarySearch(v,98,0,99) << endl;
    cout << BinarySearch(v,21398,0,9) << endl;

}

int main(char* __argc, int __argv) {
    
    // TestFactorial();
    // TestSum();
    // TestReverse();
    // TestFibo();
    // TestBinSearch();

    return 0;
}
