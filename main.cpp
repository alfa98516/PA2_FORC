#include "dynamic_array.hpp"
#include <iostream>

int main() {
    Dynamic_Vector<int> vect = Dynamic_Vector<int>();
    for (int i = 0; i < 5; ++i) {
        vect.append(i + 1);
    }

    std::cout << vect << '\n';
    int a = vect.pop();
    std::cout << vect << '\n';
    std::cout << a << '\n';
    vect.resize(7);
    std::cout << vect << '\n';
}
