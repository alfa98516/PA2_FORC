#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY
#include <cstddef>
#include <cstdlib>
#include <iostream>
template <typename T>
class Dynamic_Vector {
    T* vect;
    size_t size; // I really have not a clue how were supposed to track the
                 // length and size of the array
    size_t capacity;

    void grow() {
        capacity *= 2;
        T* _vect = new T[capacity];

        for (size_t i = 0; i < size; ++i) {
            _vect[i] = vect[i];
        }

        for (size_t i = size; i < capacity; ++i) {
            _vect[i] = T();
        }

        delete[] vect;
        vect = _vect;
    }

    void shrink() {
        if (capacity <= 1)
            return;

        capacity /= 2;

        T* _vect = new T[capacity];

        for (size_t i = 0; i < size; ++i) {
            _vect[i] = vect[i];
        }

        for (size_t i = size; i < capacity; ++i) {
            _vect[i] = T();
        }

        delete[] vect;
        vect = _vect;
    }

    /**
     * @brief this is used in both erase and insert, it moves items to their correct position
     * @param idx: the index where were inserting/deleting
     * @param mode: either 1 or 0, 1 means were inserting, 0 means were erasing.
     */
    void fix(size_t idx, int mode) {
        if (mode) { // insert mode
            if (size + 1 > capacity) grow();

            for (size_t i = size; i > idx; --i) {
                vect[i] = vect[i - 1];
            }
            size++;
        } else { // erase mode

            for (int i = idx; i < size - 1; ++i) {

                vect[i] = vect[i + 1];
            }

            size--;
            if (size <= capacity / 4) shrink();
        }
    }

  public:
    /**
     * @brief This is the base constructor, sets the capacity at 0 and the
     * size to 32 (this skips a couple resizes)
     *
     */
    Dynamic_Vector<T>()
        : size(0), capacity(32) { // initializing at 32 to skip a couple
                                  // resizes, this will not effect length
        vect = new T[capacity];
        for (int i = 0; i < capacity; ++i) {
            vect[i] = T();
        }
    }

    /**
     * @brief This constructor is kind of dumb and stupid, please use the
     * default constructor and then just resize, stupid
     * @param _capacity the capacity the user wants to initialize at
     */
    Dynamic_Vector<T>(size_t _capacity) : size(_capacity), capacity(32) {
        if (capacity < size) {
            int i = 1;
            while (i < size)  // FIXED: was "i < capacity", should be "i < size"
                i *= 2; // round up to nearest power of 2, improves efficiency of
                        // some functions. amortized; this constructor still runs in
                        // O(1)
            capacity = i;
        }

        vect = new T[capacity];
        for (int i = 0; i < capacity; ++i) {
            vect[i] = T();
        }
    }

    /**
     * @brief Copy constructor, pretty standard.
     * @param other: This is the Dynamic_Vector were copying from.
     */
    Dynamic_Vector(const Dynamic_Vector<T>& other) : size(other.len()), capacity(other.getCapacity()) {
        vect = new T[capacity];

        for (size_t i = 0; i < size; ++i) {
            vect[i] = other[i];
        }

        for (size_t i = size; i < capacity; ++i) {
            vect[i] = T();
        }
    }

    /**
     * @brief
     */
    void erase(size_t idx) {
        if (idx >= size) return;
        vect[idx] = T();
        fix(idx, 0);
    }

    /**
     * @brief Appends a new item at the end of the vector, where "end" is
     * defined as indexing with the length variable
     * @param item: the item were appending to the vector
     */
    void append(T item) {
        if (size >= capacity)
            grow();
        vect[size] = item;
        size++;
    }

    /**
     * @brief inserts an element at a given index
     * @param idx: the index the caller wants to insert at
     * @param item: the item the caller is inserting at
     */
    void insert(size_t idx, T item) {
        fix(idx, 1);
        vect[idx] = item;
    }

    T pop() {
        T item = vect[size - 1];
        vect[size - 1] = T();
        size--;
        if (size <= capacity / 4) shrink();
        return item;
    }

    /**
     * @brief its a damn len function, figure it out yourself
     * @returns size: it returns the size
     */
    const size_t len() const { return size; }

    /**
     * @brief I dont do any checking for bounds, its the callers responsability
     *         Also you should just use the insert function or the append function, i have no way to check if the caller is setting to null
     *         This overwrites whatever is at the given index
     * @param idx: the index of the item
     */
    T& operator[](size_t idx) { return vect[idx]; }

    /**
     * @brief Exactly the same as the other operator[] function, this one is just for reading
     * @param idx: the index of the item
     */
    const T& operator[](size_t idx) const { return vect[idx]; }

    const size_t getCapacity() const { return capacity; }

    void operator+(T rhs) {
        append(rhs);
    }

    Dynamic_Vector<T>& operator=(const Dynamic_Vector<T>& other) {
        if (this == &other) return *this;

        T* new_vect = new T[other.getCapacity()];
        for (size_t i = 0; i < other.len(); ++i) {
            new_vect[i] = other[i];
        }

        delete[] vect;
        vect = new_vect;
        size = other.len();
        capacity = other.getCapacity();
        return *this;
    }

    void resize(size_t _size) {
        while (_size > capacity) // dont resize to absurdly large !! thats stupid !!
            grow();
        if (_size > size) {
            for (int i = size; i < _size; ++i) {
                vect[i] = T();
            }
        }
        size = _size;
    }

    ~Dynamic_Vector<T>() { delete[] vect; }
};

#endif

#ifndef OSTREAM
#define OSTREAM
/**
 * @brief this was showin in class, i liked it so now i have it
 * @param out this is the outstream were outputting to (i.e. std::cout)
 * @param Vect: this is the vector were printing out
 * @returns out: it modifies it, and then returns it back, this is so
 * "std::cout
 * << 1 << 4 << 6;" works.
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const Dynamic_Vector<T>& Vect) {

    for (int i = 0; i < Vect.len(); ++i) {
        if (Vect.len() == i + 1) {
            out << Vect[i];
            continue;
        }
        out << Vect[i] << " ";
    }
    return out;
}

#endif
