#include "dynamic_array.hpp"
#include <cassert>
#include <iostream>

using std::cin;
using std::cout;
using std::ws;

Dynamic_Vector<int> vecs[1000];

int main() {
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int instance;
        cin >> instance;
        instance--; // change to 0-based index
        // consume whitespace before reading character, otherwise we get a space
        cin >> ws;
        char op;
        cin >> op; // read operation character

        if (op == 'a') {
            int other;
            cin >> other;
            other--; // change to 0-based index
            vecs[instance] = vecs[other];
        } else if (op == '+') {
            int value;
            cin >> value;
            vecs[instance] + value;

        } else if (op == '-') {
            int ret = vecs[instance].pop();
            cout << ret << '\n';
        } else if (op == 'i') {
            int index, value;
            cin >> index >> value;
            vecs[instance].insert(index, value);

        } else if (op == 'e') {
            int index;
            cin >> index;
            vecs[instance].erase(index);
        } else if (op == 'g') {
            int index;
            cin >> index;
            std::cout << vecs[instance][index] << '\n';
        } else if (op == 's') {
            int index, value;
            cin >> index >> value;
            // set
            vecs[instance][index] = value;
        } else if (op == 'r') {
            int sz;
            cin >> sz;

            vecs[instance].resize(sz);

        } else if (op == 'p') {
            // print
            std::cout << vecs[instance].len() << '\n';
            std::cout << vecs[instance] << '\n';
        } else {
            assert(false);
        }
    }
}
