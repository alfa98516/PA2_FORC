#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY
#include <cstddef>
#include <cstdlib>
#include <ostream>

template <typename T> class Dynamic_Vector {
  T *vect;
  size_t size; // I really have not a clue how were supposed to track the
               // length and size of the array
  size_t capacity;

  void grow() {
    capacity *= 2;
    T *_vect = new T[capacity];
    for (int i = 0; i < size; ++i) {
      _vect[i] = vect[i];
    }
    delete[] vect;
    vect = _vect;
  }

  void shrink() {
    capacity /= 2;
    T *_vect = new T[capacity];
    for (int i = 0; i < size; ++i) {
      _vect[i] = vect[i];
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
  }

  /**
   * @brief This constructor is kind of dumb and stupid, please use the
   * default constructor and then just resize, stupid
   * @param _capacity the capacity the user wants to initialize at
   */
  Dynamic_Vector<T>(size_t _capacity) : size(_capacity), capacity(32) {
    if (capacity < size) {
      int i = 1;
      while (i < capacity)
        i *= 2; // round up to nearest power of 2, improves efficiency of
                // some functions. amortized; this constructor still runs in
                // O(1)
      capacity = i;
    }

    vect = new T[capacity];
  }

  /**
   * @brief Copy constructor, pretty standard.
   * @param other: This is the Dynamic_Vector were copying from.
   */
  Dynamic_Vector(const Dynamic_Vector<T> &other) {
    vect = new T[capacity];

    for (size_t i = 0; i < size; ++i) {
      vect[i] = other[i];
    }
  }

  void erase(size_t idx) {}

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
std::ostream &operator<<(std::ostream &out, const Dynamic_Vector<T> &Vect) {
  for (int i = 0; i < Vect.len(); ++i) {
    out << Vect[i] << " ";
  }
  return out;
}

#endif
