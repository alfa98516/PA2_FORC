#include <cassert>
#include <iostream>
#include "dynamic_array.hpp"

using std::cout;
using std::cin;
using std::ws;

Dynamic_Vector<int> vects[1000];

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
            Dynamic_Vector<int> tmp = Dynamic_Vector<int>(vecs[instance]);
            vecs[other] = tmp;
        }
        else if (op == '+') {
            int value;
            cin >> value;
            
        }
        else if (op == '-') {
            int ret = vecs[instance].popback();
            cout << ret << '\n';
        }   
        else if (op == 'i') {
            int index, value;
            cin >> index >> value;
            vects[instance][index] = value;
        }   
        else if (op == 'e') {
            int index;
            cin >> index;
            vects[instance].erase(index);
        }
        else if (op == 'g') {
            int index;
            cin >> index;
            // get
            std::cout << vects[instance][index] << '\n';
        }
        else if (op == 's') {
            int index, value;
            cin >> index >> value;
            // set
            vects[instance][index] = value;
        }
        else if (op == 'r') {
            int sz;
            cin >> sz;
            // resize
        }
        else if (op == 'p') {
            // print
            std::cout << vect[instance] << '\n';
        }
        else {
            assert(false);
        }
    }
}
