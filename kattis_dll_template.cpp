#include <cassert>
#include <iostream>
#include "node.hpp"
#include "dll.hpp"

using std::cout;
using std::cin;
using std::ws;

Dll<int> dll[1000];
Node<int>* cursors[1000];

int main() {
    int q;
    cin >> q;

    for (int i = 0; i < 1000; i++) {
        cursors[i] = dll[i].back();
    }

    for (int i = 0; i < q; i++) {
        int instance;
        cin >> instance;
        instance--;
        cin >> ws;
        char op;
        cin >> op;

        if (op == 'a') {
            int other;
            cin >> other;
            other--;
            dll[instance] = dll[other];
            cursors[instance] = dll[instance].back();
        }
        else if (op == 'f') {
            cursors[instance] = dll[instance].front();
        }
        else if (op == 'b') {
            cursors[instance] = dll[instance].back();
        }
        else if (op == 'i') {
            int value;
            cin >> value;
            cursors[instance] = dll[instance].insert(cursors[instance], value);
        }
        else if (op == 'e') {
            cursors[instance] = dll[instance].erase(cursors[instance]);
        }
        else if (op == '>') {
            cursors[instance] = dll[instance].successor(cursors[instance]);
        }
        else if (op == '<') {
            cursors[instance] = dll[instance].predecessor(cursors[instance]);
        }
        else if (op == 'g') {
            cout << cursors[instance]->data << '\n';
        }
        else if (op == 's') {
            int value;
            cin >> value;
            cursors[instance]->data = value;
        }
        else if (op == 'z') {
            cout << dll[instance].size() << '\n';
        }
        else {
            assert(false);
        }
    }
}