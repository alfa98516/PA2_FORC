#include <iostream>
#include "dynamic_array.hpp"
#include "dll.hpp"


int main() {
    Dll<int> dll;

    Node<int>* n1 = dll.insert(dll.back(), 2);
    Node<int>* n2 = dll.insert(n1, 5);

    std::cout<<dll.erase(n2)->data<<std::endl;
    std::cout<<dll.erase(n1)->
    data<<std::endl;

}   
