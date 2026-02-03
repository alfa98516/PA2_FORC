#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY
#include <cstdlib>

template <typename T>
class Dynamic_Vector{
    private:
    
    T* vect;
    int size;
    int capacity;
    
    public:
     
    Dynamic_Vector<T>(int _size): size(_size) {
        vect = new T[size];
        capacity = size;        
        
    }

    Dynamic_Vector<T>() {
        size = 2;
        capacity = 2;
        vect = new T[size];

    }

    T popback() {}

    void addItem(T item) {}



};

#endif
