#include <cassert>
#include <cstring>
#include <cstdio>

#include <iostream>
// can use strlen, strcat, strcpy, atoi, atof, memcpy, assert
#include "hashtable.hpp"

int main() {
    int q;
    std::cin >> q;

    HashTable<int> ht[1001];

    for (int i = 0; i < q; i++) {
        int id;
        char op;
        std::cin >> id >> op;

        if (op == 'a') {
            int copy_id;
            std::cin >> copy_id;
            ht[id] = ht[copy_id];
        } else if (op == 'i') {
            int key;
            int value;
            std::cin >> key >> value;
            ht[id].insert(key, value);
        } else if (op == 'e') {
            ht[id].erase();
        } else if (op == 'g') {
            int key;
            int value;
            std::cin >> key >> value;
            ht[id].get(key, value);
        } else if (op == 's') {
            int key;
            int value;
            std::cin >> key >> value;
            ht[id].set(key, value);
        } else if (op == 'z') {
            ht[id].size();
        }
    }

    return 0;
}

