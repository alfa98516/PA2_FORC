#include <cassert>
#include <cstdio>
#include <cstring>

#include <iostream>
// can use strlen, strcat, strcpy, atoi, atof, memcpy, assert
#include "hashtable.hpp"

int main() {
    int q;
    std::cin >> q;

    HashMap<int, int> ht[1001];

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
            int key;
            std::cin >> key;
            ht[id].remove(key);
        } else if (op == 'g') {
            int key;
            std::cin >> key;
            int value = ht[id].find(key);
            if (ht[id].contains(key))
                std::cout << value << '\n';
            else
                std::cout << "-\n";
        } else if (op == 's') {
            int key;
            int value;
            std::cin >> key >> value;
            ht[id].update(key, value);
        } else if (op == 'z') {
            size_t size = ht[id].size();
            std::cout << size << '\n';
        }
    }

    return 0;
}
