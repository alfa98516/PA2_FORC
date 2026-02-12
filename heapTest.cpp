#include <cassert>
#include <cstring>
#include <cstdio>

#include <iostream>
// can use strlen, strcat, strcpy, atoi, atof, memcpy, assert
#include "heap.hpp"

int main() {
    MinHeap<int> h;
    h.push(4);
    h.getAll();
    h.push(7);
    h.push(1);
    h.getAll();
    std:: cout << "PEEK: " << h.peek() << std::endl;
    h.push(2);
    h.pop();
    h.getAll();
    
    return 0;
}

/*  RUN
g++ -std=c++98 heapTest.cpp -o heap2
./heap2
*/