#include <iostream>
#include "dynamic_array.hpp"


int main() {
    Dynamic_Vector<int> vect = Dynamic_Vector<int>();
    for(int i = 0; i<100; ++i) {
        vect.append(i);
    }
    std::cout << vect.len() << '\n';
}   
