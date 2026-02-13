#include <cassert>
#include <cstring>
#include <cstdio>

#include <iostream>
// can use strlen, strcat, strcpy, atoi, atof, memcpy, assert
#include "dll.hpp"

int main() {
    int q;
    std::cin >> q;

    Dll<int> dll[1001];
    Node<int>* cursor[1001];
    
    // Initialize all cursors to the tail (sentinel node)
    for (int i = 0; i <= 1000; i++) {
        cursor[i] = dll[i].back();
    }

    for (int i = 0; i < q; i++) {
        int id;
        char op;
        std::cin >> id >> op;

        if (op == 'a') {
            int copy_id;
            std::cin >> copy_id;
            dll[id] = dll[copy_id];
            cursor[id] = dll[id].back(); // Reset cursor to sentinel after assignment
        } else if (op == 'f') {
            cursor[id] = dll[id].front();
        } else if (op == 'b') {
            cursor[id] = dll[id].back();
        } else if (op == 'i') {
            int value;
            std::cin >> value;
            cursor[id] = dll[id].insert(cursor[id], value);
        } else if (op == 'e') {
            cursor[id] = dll[id].erase(cursor[id]);
        } else if (op == '>') {
            cursor[id] = dll[id].successor(cursor[id]);
        } else if (op == '<') {
            cursor[id] = dll[id].predecessor(cursor[id]);
        } else if (op == 'g') {
            std::cout << cursor[id]->data << std::endl;
        } else if (op == 's') {
            int x;
            std::cin >> x;
            cursor[id]->data = x;
        } else if (op == 'z') {
            std::cout << dll[id].size() << std::endl;
        }
    }

    return 0;
}