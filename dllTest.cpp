#include <cassert>
#include <cstring>
#include <cstdio>

#include <iostream>
// can use strlen, strcat, strcpy, atoi, atof, memcpy, assert
#include "dll.hpp"

int main() {
    int q;
    std::cin >> q;

    Dll<int> dll[1000];


    for (int i = 0; i < q; i++) {
        int id;
        char op;
        std::cin >> id >> op;
        Node<int>* node = dll[id].front();

        if (op == 'a') {
            int copy_id;
            std::cin >> copy_id;
            dll[id] = dll[copy_id];
        } else if (op == 'f') {
            std::cout << dll[id].front()->data << std::endl;
        } else if (op == 'b') {
            std::cout << dll[id].back()->data << std::endl;
        } else if (op == 'i') {
            dll[id].insert(node, 10);
        } else if (op == 'e') {
            dll[id].erase(node);
        } else if (op == '>') {
            dll[id].successor(node);
        } else if (op == '<') {
            dll[id].predecessor(node);
        } else if (op == 'g') {
            if (node != NULL)
                std::cout << node->data << std::endl;
        } else if (op == 's') {
            int x;
            std::cin >> x;
            if (node != NULL) {
                node->data = x;
                std::cout << node->data << std::endl;
            }
        } else if (op == 'z') {
            std::cout << dll[id].size() << std::endl;
        }
    }

    return 0;
}
