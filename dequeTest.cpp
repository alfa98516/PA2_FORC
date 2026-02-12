#include <cassert>
#include <cstring>
#include <cstdio>

#include <iostream>
// can use strlen, strcat, strcpy, atoi, atof, memcpy, assert
#include "dequeue.hpp"

int main() {

    Dequeue<int> dq;
    dq.push_back(7);
    dq.push_back(8);
    dq.push_front(6);
    dq.push_front(5);
    dq.push_back(9);
    dq.pop_front();
    dq.pop_back();
    dq.debugging();
    std::cout << std::endl;
    dq.pop_back();
    dq.debugging();
    std::cout << std::endl;
    dq.pop_back();
    dq.debugging();
    std::cout << std::endl;
    dq.pop_back();
    dq.pop_front();
    dq.debugging();

    
    return 0;
}

/* RUN
g++ -std=c++98 dequeTest.cpp -o deque
./deque

Output:
Capacity: 4
Size: 3
Head: 0
Rear: 2
Head value: 6
Rear value: 8
6 7 8 

Capacity: 4
Size: 2
Head: 0
Rear: 1
Head value: 6
Rear value: 7
6 7 

Capacity: 2
Size: 1
Head: 0
Rear: 0
Head value: 6
Rear value: 6
6 

Deque is empty
Capacity: 2
Size: 0
Head: 0
Rear: 0
Deque is empty — no head/rear value
*/