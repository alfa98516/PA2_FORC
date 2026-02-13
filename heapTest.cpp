#include <cassert>
#include <cstring>
#include <cstdio>

#include <iostream>
// can use strlen, strcat, strcpy, atoi, atof, memcpy, assert
#include "heap.hpp"

int main() {
    int q;
    std::cin >> q;

    MinHeap<int> h[1001];

    for (int i = 0; i < q; i++) {
        int id;
        char op;
        std::cin >> id >> op;

        if (op == 'a') {
            int copy_id;
            std::cin >> copy_id;
            h[id] = h[copy_id];
        }
        else if (op == '+') {
            int value;
            std::cin >> value;
            h[id].push(value);
        }
        else if (op == '-') {
            h[id].pop();
        }
        else if (op == 'p') {
            std::cout << h[id].peek() << std::endl;
        }
        else if (op == 's') {
            std::cout << h[id].size() << std::endl;
        }
    }

    return 0;
}

