#include <iostream>
#include "dynamic_array.hpp"


int main() {
    Dynamic_Vector<int> vect;
    
    vect.append(1);
    vect[0] = 2;
    int tmp = vect[0];
    vect[0] = 7;
    
    vect.append(4);
    vect.append(6);
    vect.append(5);
    vect.append(8);
    vect.append(10);
    vect.append(94);
    vect.
    for (int i = 0; i<vect.len(); ++i) {
        std::cout << vect[i] << '\n';
    }
    std::cout << vect << '\n';
    
    vect + 3;
    Dynamic_Vector<int> cpy = Dynamic_Vector<int>(vect);
    
    std::cout << cpy[0] << " " << vect[0] << '\n';
    cpy[0] = 5;
    tmp = cpy[0];
    std::cout << tmp << '\n';
}
