#include "node.hpp"

#ifndef HT
#define HT

template <typename T>
class HashTable {
    private:

        int count;
    public:

        void insert(int key, T value) {

        }

        void erase() {

        }

        T get(int key, T value) {
            // if hash table empty return  type (T())
            return T();

            // else return value
        }

        void set(int key, T value) {
            
        }

        int size () {
            return count;
        }
}

#endif