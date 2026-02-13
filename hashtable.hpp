#include "node.hpp"

#ifndef HT
#define HT

template <typename T>
class HashTable {
    private:

        int count;
    public:

        void insert(int key, T value) {
            // insert a key-value pair to the hash table if the key does not exist, otherwise do nothing

        }

        void erase() {
            // erase a given key from the hash table which is guaranteed to exist
        }

        T get(int key, T value) {
            // element access, get, output the value associated with the given key if it exists, see output section
            // if hash table empty return  type (T())
            return T();

            // else return value
        }

        void set(int key, T value) {
            // element access, set, set the value associated with a given key which is guaranteed to exist
        }

        int size () {
            // output size of hash table, see output section
            return count;
        }
}

#endif