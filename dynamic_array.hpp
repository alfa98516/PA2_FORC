#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY
#include <cstdlib>
#include <algorithm>
#include <ostream>

template <typename T>
class Dynamic_Vector{
    private:
    
    T* vect;
    size_t size;
    int capacity;
    
    void grow() {
        capacity+=size;
        size *= 2;
        T* _vect = new T[size];
        for (int i = 0; i<len(); ++i) {
            _vect[i] = vect[i];
        }
        delete vect;
        vect = _vect;

    }
    
    void shrink() {
        size/=2;
        T* _vect = new T[size];
        for (int i = 0; i<len(); ++i) {
            _vect[i] = vect[i];
        }
        
        delete vect;
        vect = _vect;
    }

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

    Dynamic_Vector<T>(const Dynamic_Vector &other) : size(other.size), capacity(other.capacity){
        vect = new T[size];
        for (int i = 0; i<size; ++i){
            vect[i] = other[i];
        }
    }

    T popback() {
        T ret = vect[size];
        vect[size-1] = NULL;
        capacity++;
        if (capacity <= size/4) shrink();
        return ret;
    }

    void append(T item) {
        if(capacity <= 0) grow();
        vect[size-capacity] = item;
        capacity--;
    }
    
    // whenever the user does something like "a = vect[0]" this function gets called 
    // otherwise it the other operator[] function gets called 
    // this is very useful for the copy constructor.
    const T& operator[](size_t index) const {
        if (index >= size) exit(1);
        return vect[index];
    }
    
    // please use this responsably, dont set to null that would be dumb
    T& operator[](size_t index) {
        if (index >= size) exit(1);
        return vect[index];
    }
    
    void erase(size_t index) {
        
    }

    // better as const and also allows me to use the ostream operator<< function.
    const size_t len() const{
        return size-capacity-1;
    }

    void operator+(T rhs) {
        append(rhs);
    }

};
#endif

#ifndef OSTREAM
#define OSTREAM
template<typename T>
std::ostream& operator<<(std::ostream& out, const Dynamic_Vector<T> &Vect) {
    out << Vect.len() << '\n';
    for(int i = 1; i<Vect.len(); ++i) {
        out << Vect[i] << " ";
    }
    return out;
}

#endif
