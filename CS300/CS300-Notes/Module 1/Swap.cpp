
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

template <class T>
void Swap(T& a, T& b) {
    T _t = a;
    a = b;
    b = _t;
}

void TestSwap()
{
    int x = 10;
    int y = 99;

    Swap(x, y);

    std::cout << x << " : " << y << std::endl;
}


int main(char* __argc, int __argv) {

    TestSwap();

    return 0;
}



