#include <cassert>
#include <cstring>
#include <cstdio>

#include <iostream>
// can use strlen, strcat, strcpy, atoi, atof, memcpy, assert
#include "dequeue.hpp"

int main() {
    int q;
    std::cin >> q;

    Dequeue<int> dq[1001];

    for (int i = 0; i < q; i++) {
        int id;
        char op;
        std::cin >> id >> op;

        if (op == 'a') {
            int copy_id;
            std::cin >> copy_id;
            dq[id] = dq[copy_id];
        } else if (op == '+') {
            char action;
            std::cin >> action;
            if (action == 'f') {
                int value;
                std::cin >> value;
                dq[id].push_front(value);
            } else if (action == 'b') {
                int value;
                std::cin >> value;
                dq[id].push_back(value);
            }
        } else if (op == '-') {
            char action;
            std::cin >> action;
            if (action == 'f') {
                dq[id].pop_front();
            } else if (action == 'b') {
                dq[id].pop_back();
            }
        } else if (op == 'f') {
            std::cout << dq[id].front() << std::endl;
        } else if (op == 'b') {
            std::cout << dq[id].back() << std::endl;
        } else if (op == 's') {
            std::cout << dq[id].size() << std::endl;
        }
    }

    return 0;
}

